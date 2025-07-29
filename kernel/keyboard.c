#include "keyboard.h"
#include "vga.h"
#include "ports.h"
#include "string.h"
#include "timer.h"
#include "memory.h"
#include "calculator.h"
#include "games.h"
#include "cybersec.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

static char input_buffer[256];
static size_t input_length = 0;

// US QWERTY scancode to ASCII mapping
static char scancode_to_ascii[] = {
    0,  0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

void keyboard_init(void) {
    input_length = 0;
    memset(input_buffer, 0, sizeof(input_buffer));
}

static void process_command(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        vga_print("\n╔═══════════════════════════════════════════════════════════════╗\n");
        vga_print("║                        CYBEROS COMMANDS                       ║\n");
        vga_print("╠═══════════════════════════════════════════════════════════════╣\n");
        vga_print("║ SYSTEM:                    │ CYBERSECURITY:                   ║\n");
        vga_print("║  help      - Show commands │  netscan     - Network scanner   ║\n");
        vga_print("║  clear     - Clear screen  │  vulnscan    - Vulnerability scan║\n");
        vga_print("║  info      - System info   │  firewall    - Firewall demo     ║\n");
        vga_print("║  halt      - Shutdown      │  ids         - Intrusion detect ║\n");
        vga_print("║  uptime    - System uptime │  forensics   - Memory analysis   ║\n");
        vga_print("║  memory    - Memory status │  pwdcheck    - Password analyzer ║\n");
        vga_print("║  date      - Current time  │  hash        - Hash generator    ║\n");
        vga_print("║                            │  encrypt     - Encryption tool   ║\n");
        vga_print("║ UTILITIES:                 │                                  ║\n");
        vga_print("║  calc [expr] - Calculator  │ GAMES & FUN:                     ║\n");
        vga_print("║  theme [name] - Themes     │  snake       - Snake game        ║\n");
        vga_print("║  matrix       - Matrix FX  │  guess       - Number game       ║\n");
        vga_print("║  rainbow      - Rainbow    │  logo        - Show logo         ║\n");
        vga_print("╚═══════════════════════════════════════════════════════════════╝\n");
        vga_print("Type 'cybersec' for detailed cybersecurity command help.\n");
    }
    else if (strcmp(cmd, "cybersec") == 0) {
        vga_print("\n╔═══════════════════════════════════════════════════════════════╗\n");
        vga_print("║                    CYBERSECURITY TOOLKIT                      ║\n");
        vga_print("╠═══════════════════════════════════════════════════════════════╣\n");
        vga_print("║ NETWORK SECURITY:          │ CRYPTOGRAPHY:                    ║\n");
        vga_print("║  netscan     - Scan network │  hash [text] [algo] - Generate  ║\n");
        vga_print("║  firewall    - Firewall sim │  encrypt [text] [key] - Encrypt ║\n");
        vga_print("║  ids         - Monitor IDS  │  pwdcheck [pwd] - Check strength║\n");
        vga_print("║                             │  pwdgen - Generate secure pwd   ║\n");
        vga_print("║ SYSTEM SECURITY:           │                                  ║\n");
        vga_print("║  vulnscan    - Vuln scanner │ FORENSICS:                       ║\n");
        vga_print("║  integrity   - System check │  forensics - Memory analysis    ║\n");
        vga_print("║  access      - Access demo  │  logs      - Log analyzer       ║\n");
        vga_print("║                             │  recover   - File recovery      ║\n");
        vga_print("╠═══════════════════════════════════════════════════════════════╣\n");
        vga_print("║ Examples:                                                     ║\n");
        vga_print("║  hash \"password123\" simple                                   ║\n");
        vga_print("║  encrypt \"secret\" \"key\"                                      ║\n");
        vga_print("║  pwdcheck \"MyP@ssw0rd!\"                                       ║\n");
        vga_print("╚═══════════════════════════════════════════════════════════════╝\n");
    }
    // Network Security Commands
    else if (strcmp(cmd, "netscan") == 0) {
        network_scanner();
    }
    else if (strcmp(cmd, "firewall") == 0) {
        firewall_simulator();
    }
    else if (strcmp(cmd, "ids") == 0) {
        ids_monitor();
    }
    // System Security Commands  
    else if (strcmp(cmd, "vulnscan") == 0) {
        vulnerability_scanner();
    }
    else if (strcmp(cmd, "integrity") == 0) {
        system_integrity_check();
    }
    else if (strcmp(cmd, "access") == 0) {
        access_control_demo();
    }
    // Forensics Commands
    else if (strcmp(cmd, "forensics") == 0) {
        memory_dump_analyzer();
    }
    else if (strcmp(cmd, "logs") == 0) {
        log_analyzer();
    }
    else if (strcmp(cmd, "recover") == 0) {
        file_recovery_simulator();
    }
    // Cryptography Commands
    else if (strlen(cmd) > 5 && cmd[0] == 'h' && cmd[1] == 'a' && cmd[2] == 's' && cmd[3] == 'h' && cmd[4] == ' ') {
        // Parse hash command: hash "text" algorithm
        const char* args = cmd + 5;
        char text[64] = {0};
        char algo[16] = {0};
        
        // Simple parsing - extract text and algorithm
        int i = 0, j = 0;
        if (args[0] == '"') {
            i = 1; // Skip opening quote
            while (args[i] && args[i] != '"' && j < 63) {
                text[j++] = args[i++];
            }
            if (args[i] == '"') i++; // Skip closing quote
            while (args[i] == ' ') i++; // Skip spaces
            j = 0;
            while (args[i] && j < 15) {
                algo[j++] = args[i++];
            }
        } else {
            // No quotes, parse until space
            while (args[i] && args[i] != ' ' && j < 63) {
                text[j++] = args[i++];
            }
            while (args[i] == ' ') i++; // Skip spaces
            j = 0;
            while (args[i] && j < 15) {
                algo[j++] = args[i++];
            }
        }
        
        if (strlen(text) > 0 && strlen(algo) > 0) {
            hash_generator(text, algo);
        } else {
            vga_print("\nUsage: hash \"text\" algorithm\n");
            vga_print("Algorithms: simple, crc32\n");
            vga_print("Example: hash \"password123\" simple\n");
        }
    }
    else if (strlen(cmd) > 8 && strncmp(cmd, "encrypt ", 8) == 0) {
        // Parse encrypt command: encrypt "text" "key"
        const char* args = cmd + 8;
        char text[64] = {0};
        char key[32] = {0};
        
        // Simple parsing for encrypted text and key
        int i = 0, j = 0;
        if (args[0] == '"') {
            i = 1; // Skip opening quote
            while (args[i] && args[i] != '"' && j < 63) {
                text[j++] = args[i++];
            }
            if (args[i] == '"') i++; // Skip closing quote
            while (args[i] == ' ') i++; // Skip spaces
            if (args[i] == '"') i++; // Skip opening quote for key
            j = 0;
            while (args[i] && args[i] != '"' && j < 31) {
                key[j++] = args[i++];
            }
        }
        
        if (strlen(text) > 0 && strlen(key) > 0) {
            encryption_tool(text, key);
        } else {
            vga_print("\nUsage: encrypt \"text\" \"key\"\n");
            vga_print("Example: encrypt \"secret\" \"mykey\"\n");
        }
    }
    else if (strlen(cmd) > 9 && strncmp(cmd, "pwdcheck ", 9) == 0) {
        const char* password = cmd + 9;
        if (password[0] == '"') {
            // Extract password from quotes
            char pwd[64] = {0};
            int i = 1, j = 0;
            while (password[i] && password[i] != '"' && j < 63) {
                pwd[j++] = password[i++];
            }
            password_analyzer(pwd);
        } else {
            password_analyzer(password);
        }
    }
    else if (strcmp(cmd, "pwdgen") == 0) {
        char password[17];
        generate_secure_password(password, 17);
        vga_print("\nGenerated secure password: ");
        vga_print(password);
        vga_print("\nNote: This is a demonstration. Use proper entropy sources in production.\n");
    }
    else if (strcmp(cmd, "clear") == 0) {
        vga_clear_screen();
        vga_print("cyberos> ");
        return;
    }
    else if (strcmp(cmd, "info") == 0) {
        vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
        vga_print("║                        SYSTEM INFORMATION                    ║\n");
        vga_print("╠══════════════════════════════════════════════════════════════╣\n");
        vga_print("║ OS Name:     CyberOS Advanced v2.0                          ║\n");
        vga_print("║ Architecture: x86 (32-bit)                                  ║\n");
        vga_print("║ Built:       July 2025                                      ║\n");
        vga_print("║ Purpose:     Cybersecurity Education                        ║\n");
        vga_print("║ Display:     VGA Text Mode 80x25                            ║\n");
        vga_print("║ Features:    Memory Mgmt, Timer, Calculator, Games          ║\n");
        
        struct memory_stats stats;
        get_memory_stats(&stats);
        vga_print("║ Memory:      ");
        vga_print_hex(stats.used_memory);
        vga_print(" / ");
        vga_print_hex(stats.total_memory);
        vga_print(" bytes used         ║\n");
        
        vga_print("║ Uptime:      ");
        uint32_t uptime = get_uptime_seconds();
        vga_print_hex(uptime);
        vga_print(" seconds                              ║\n");
        vga_print("╚══════════════════════════════════════════════════════════════╝\n");
    }
    else if (strcmp(cmd, "uptime") == 0) {
        uint32_t seconds = get_uptime_seconds();
        uint32_t minutes = seconds / 60;
        uint32_t hours = minutes / 60;
        
        vga_print("\nSystem Uptime: ");
        vga_print_hex(hours);
        vga_print("h ");
        vga_print_hex(minutes % 60);
        vga_print("m ");
        vga_print_hex(seconds % 60);
        vga_print("s\n");
    }
    else if (strcmp(cmd, "memory") == 0) {
        struct memory_stats stats;
        get_memory_stats(&stats);
        
        vga_print("\n┌─────────────────────────────────────┐\n");
        vga_print("│           MEMORY STATUS             │\n");
        vga_print("├─────────────────────────────────────┤\n");
        vga_print("│ Total Memory:  ");
        vga_print_hex(stats.total_memory);
        vga_print(" bytes       │\n");
        vga_print("│ Used Memory:   ");
        vga_print_hex(stats.used_memory);
        vga_print(" bytes       │\n");
        vga_print("│ Free Memory:   ");
        vga_print_hex(stats.free_memory);
        vga_print(" bytes       │\n");
        vga_print("│ Alloc Blocks:  ");
        vga_print_hex(stats.allocated_blocks);
        vga_print("                 │\n");
        vga_print("└─────────────────────────────────────┘\n");
    }
    else if (strlen(cmd) > 5 && cmd[0] == 'c' && cmd[1] == 'a' && cmd[2] == 'l' && cmd[3] == 'c' && cmd[4] == ' ') {
        const char* expr = cmd + 5; // Skip "calc "
        int32_t result = evaluate_expression(expr);
        vga_print("\nResult: ");
        vga_print_hex(result);
        vga_print("\n");
    }
    else if (strcmp(cmd, "calc") == 0) {
        print_calculator_help();
    }
    else if (strcmp(cmd, "snake") == 0) {
        snake_game();
    }
    else if (strcmp(cmd, "guess") == 0) {
        number_guessing_game();
    }
    else if (strcmp(cmd, "logo") == 0) {
        vga_clear_screen();
        display_cyberos_logo();
        vga_print("\nPress any key to continue...\n");
    }
    else if (strcmp(cmd, "matrix") == 0) {
        display_matrix_effect();
    }
    else if (strcmp(cmd, "theme green") == 0) {
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("\nTheme changed to: Matrix Green\n");
    }
    else if (strcmp(cmd, "theme blue") == 0) {
        vga_set_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
        vga_print("\nTheme changed to: Ocean Blue\n");
    }
    else if (strcmp(cmd, "theme red") == 0) {
        vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        vga_print("\nTheme changed to: Alert Red\n");
    }
    else if (strcmp(cmd, "theme") == 0) {
        vga_print("\nAvailable themes:\n");
        vga_print("  theme green - Matrix Green (default)\n");
        vga_print("  theme blue  - Ocean Blue\n");
        vga_print("  theme red   - Alert Red\n");
    }
    else if (strcmp(cmd, "rainbow") == 0) {
        const char* text = "CyberOS Rainbow Mode!";
        enum vga_color colors[] = {
            VGA_COLOR_RED, VGA_COLOR_LIGHT_RED, VGA_COLOR_BROWN,
            VGA_COLOR_LIGHT_BROWN, VGA_COLOR_GREEN, VGA_COLOR_LIGHT_GREEN,
            VGA_COLOR_CYAN, VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLUE,
            VGA_COLOR_LIGHT_BLUE, VGA_COLOR_MAGENTA, VGA_COLOR_LIGHT_MAGENTA
        };
        
        vga_print("\n");
        for (int i = 0; text[i]; i++) {
            vga_set_color(colors[i % 12], VGA_COLOR_BLACK);
            vga_putchar(text[i]);
        }
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("\n");
    }
    else if (strcmp(cmd, "date") == 0) {
        uint32_t uptime = get_uptime_seconds();
        vga_print("\nSystem started ");
        vga_print_hex(uptime);
        vga_print(" seconds ago\n");
        vga_print("Current session: July 29, 2025\n");
    }
    else if (strcmp(cmd, "halt") == 0) {
        vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        vga_print("\n");
        vga_print("╔═══════════════════════════════════════╗\n");
        vga_print("║          SHUTTING DOWN CYBEROS        ║\n");
        vga_print("║                                       ║\n");
        vga_print("║  Thank you for using CyberOS!         ║\n");
        vga_print("║  It's now safe to turn off your       ║\n");
        vga_print("║  computer or close the emulator.      ║\n");
        vga_print("║                                       ║\n");
        vga_print("║        System Halted Successfully     ║\n");
        vga_print("╚═══════════════════════════════════════╝\n");
        asm volatile("cli; hlt");
    }
    else if (strlen(cmd) > 0) {
        vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        vga_print("\nUnknown command: '");
        vga_print(cmd);
        vga_print("'\n");
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("Type 'help' for available commands.\n");
    }
    
    vga_print("cyberos> ");
}

void keyboard_handler(void) {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    
    // Only handle key press events (bit 7 clear)
    if (scancode & 0x80) {
        return;
    }
    
    // Convert scancode to ASCII
    if (scancode < sizeof(scancode_to_ascii)) {
        char ascii = scancode_to_ascii[scancode];
        
        if (ascii == '\n') {
            // Enter key pressed - process command
            input_buffer[input_length] = '\0';
            process_command(input_buffer);
            input_length = 0;
            memset(input_buffer, 0, sizeof(input_buffer));
        }
        else if (ascii == '\b') {
            // Backspace key pressed
            if (input_length > 0) {
                input_length--;
                input_buffer[input_length] = '\0';
                vga_print("\b \b"); // Move cursor back, print space, move back again
            }
        }
        else if (ascii != 0 && input_length < sizeof(input_buffer) - 1) {
            // Regular character
            input_buffer[input_length] = ascii;
            input_length++;
            vga_putchar(ascii);
        }
    }
}

void keyboard_update(void) {
    // Check if keyboard data is available
    uint8_t status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keyboard_handler();
    }
}
