#include "cybersec.h"
#include "vga.h"
#include "string.h"
#include "timer.h"

// Simple hash function for demonstration
uint32_t simple_hash(const char* data) {
    uint32_t hash = 5381;
    int c;
    while ((c = *data++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// CRC32 implementation for file integrity
uint32_t crc32_hash(const char* data, size_t len) {
    uint32_t crc = 0xFFFFFFFF;
    static const uint32_t crc_table[256] = {
        0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, // First few entries
        // ... (simplified table for demo)
    };
    
    for (size_t i = 0; i < len; i++) {
        crc = crc_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ 0xFFFFFFFF;
}

void hash_generator(const char* input, const char* algorithm) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                    HASH GENERATOR                             ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Input: ");
    vga_print(input);
    for (int i = strlen(input); i < 45; i++) vga_print(" ");
    vga_print("║\n");
    vga_print("║ Algorithm: ");
    vga_print(algorithm);
    for (int i = strlen(algorithm); i < 40; i++) vga_print(" ");
    vga_print("║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    
    if (strcmp(algorithm, "simple") == 0) {
        uint32_t hash = simple_hash(input);
        vga_print("║ Simple Hash: ");
        vga_print_hex(hash);
        vga_print("                                    ║\n");
    } else if (strcmp(algorithm, "crc32") == 0) {
        uint32_t hash = crc32_hash(input, strlen(input));
        vga_print("║ CRC32 Hash:  ");
        vga_print_hex(hash);
        vga_print("                                    ║\n");
    } else {
        vga_print("║ Unsupported algorithm. Use: simple, crc32                   ║\n");
    }
    
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

int password_strength_score(const char* password) {
    int score = 0;
    int len = strlen(password);
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    
    // Length scoring
    if (len >= 8) score += 2;
    if (len >= 12) score += 2;
    if (len >= 16) score += 2;
    
    // Character type scoring
    for (int i = 0; i < len; i++) {
        char c = password[i];
        if (c >= 'A' && c <= 'Z') has_upper = 1;
        if (c >= 'a' && c <= 'z') has_lower = 1;
        if (c >= '0' && c <= '9') has_digit = 1;
        if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || 
            c == '^' || c == '&' || c == '*') has_special = 1;
    }
    
    score += has_upper * 2;
    score += has_lower * 2;
    score += has_digit * 2;
    score += has_special * 3;
    
    return score;
}

void password_analyzer(const char* password) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                  PASSWORD STRENGTH ANALYZER                  ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    
    int score = password_strength_score(password);
    int len = strlen(password);
    
    vga_print("║ Password Length: ");
    vga_print_hex(len);
    vga_print(" characters                                ║\n");
    vga_print("║ Strength Score:  ");
    vga_print_hex(score);
    vga_print("/15                                         ║\n");
    vga_print("║                                                              ║\n");
    
    if (score < 5) {
        vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        vga_print("║ Rating: WEAK - Easily cracked                               ║\n");
    } else if (score < 10) {
        vga_set_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK);
        vga_print("║ Rating: MODERATE - Needs improvement                        ║\n");
    } else {
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("║ Rating: STRONG - Good security                              ║\n");
    }
    
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("║                                                              ║\n");
    vga_print("║ Recommendations:                                             ║\n");
    
    if (len < 8) {
        vga_print("║ • Use at least 8 characters                                 ║\n");
    }
    if (!strchr(password, '!') && !strchr(password, '@')) {
        vga_print("║ • Add special characters (!@#$%^&*)                         ║\n");
    }
    vga_print("║ • Mix uppercase, lowercase, numbers, symbols                ║\n");
    vga_print("║ • Avoid dictionary words and personal info                  ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void generate_secure_password(char* buffer, size_t length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*";
    static uint32_t seed = 12345;
    
    for (size_t i = 0; i < length - 1; i++) {
        seed = seed * 1103515245 + 12345;
        buffer[i] = charset[seed % (sizeof(charset) - 1)];
    }
    buffer[length - 1] = '\0';
}

void encryption_tool(const char* text, const char* key) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                    ENCRYPTION TOOL (XOR)                     ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Plaintext:  ");
    vga_print(text);
    for (int i = strlen(text); i < 42; i++) vga_print(" ");
    vga_print("║\n");
    vga_print("║ Key:        ");
    vga_print(key);
    for (int i = strlen(key); i < 42; i++) vga_print(" ");
    vga_print("║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Encrypted:  ");
    
    int key_len = strlen(key);
    for (int i = 0; text[i]; i++) {
        char encrypted = text[i] ^ key[i % key_len];
        vga_print_hex((uint8_t)encrypted);
        vga_print(" ");
    }
    vga_print("\n║                                                              ║\n");
    vga_print("║ Note: XOR cipher for educational purposes only              ║\n");
    vga_print("║ Use AES/RSA for real-world encryption                       ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void network_scanner(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                    NETWORK SECURITY SCANNER                  ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Scanning local network range: 192.168.1.0/24                ║\n");
    vga_print("║                                                              ║\n");
    
    const char* hosts[] = {
        "192.168.1.1   - Router          [OPEN: 22,80,443]",
        "192.168.1.100 - Windows PC      [OPEN: 135,139,445]",
        "192.168.1.101 - Linux Server    [OPEN: 22,80,3306]",
        "192.168.1.102 - IoT Device      [OPEN: 80,8080]",
        "192.168.1.103 - Printer         [OPEN: 9100,515]"
    };
    
    for (int i = 0; i < 5; i++) {
        vga_print("║ ");
        vga_print(hosts[i]);
        for (int j = strlen(hosts[i]); j < 60; j++) vga_print(" ");
        vga_print("║\n");
        delay_ms(500); // Simulate scanning delay
    }
    
    vga_print("║                                                              ║\n");
    vga_print("║ Potential Vulnerabilities Found:                            ║\n");
    vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    vga_print("║ • Weak SSH configuration on 192.168.1.101                   ║\n");
    vga_print("║ • Unencrypted web interface on IoT device                   ║\n");
    vga_print("║ • Default credentials likely on printer                     ║\n");
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void vulnerability_scanner(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                  SYSTEM VULNERABILITY SCANNER                ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Scanning CyberOS system components...                       ║\n");
    vga_print("║                                                              ║\n");
    
    const char* checks[] = {
        "Kernel memory protection",
        "Stack overflow prevention", 
        "Buffer overflow detection",
        "Privilege escalation vectors",
        "Interrupt handler security",
        "Memory allocation bounds"
    };
    
    const char* results[] = {
        "PASS",
        "WARN", 
        "PASS",
        "FAIL",
        "PASS",
        "WARN"
    };
    
    for (int i = 0; i < 6; i++) {
        vga_print("║ ");
        vga_print(checks[i]);
        for (int j = strlen(checks[i]); j < 35; j++) vga_print(" ");
        
        if (strcmp(results[i], "PASS") == 0) {
            vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        } else if (strcmp(results[i], "WARN") == 0) {
            vga_set_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK);
        } else {
            vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        }
        
        vga_print("[");
        vga_print(results[i]);
        vga_print("]");
        
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        for (int j = strlen(results[i]); j < 20; j++) vga_print(" ");
        vga_print("║\n");
        
        delay_ms(300);
    }
    
    vga_print("║                                                              ║\n");
    vga_print("║ Critical Issues Found: 1                                    ║\n");
    vga_print("║ Warnings: 2                                                 ║\n");
    vga_print("║ Recommendations: Implement privilege separation             ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void firewall_simulator(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                     FIREWALL SIMULATOR                       ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Current Rules:                                               ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ 1. ALLOW  SSH (22)     from 192.168.1.0/24                  ║\n");
    vga_print("║ 2. ALLOW  HTTP (80)    from ANY                             ║\n");
    vga_print("║ 3. ALLOW  HTTPS (443)  from ANY                             ║\n");
    vga_print("║ 4. BLOCK  Telnet (23)  from ANY                             ║\n");
    vga_print("║ 5. BLOCK  FTP (21)     from ANY                             ║\n");
    vga_print("║ 6. ALLOW  DNS (53)     to 8.8.8.8                          ║\n");
    vga_print("║ 7. DENY   ALL          (default)                            ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Simulating incoming connections...                          ║\n");
    vga_print("║                                                              ║\n");
    
    const char* connections[] = {
        "192.168.1.50:2234 -> :22   ",
        "10.0.0.1:5555 -> :23       ",
        "203.0.113.1:1234 -> :80    ",
        "192.168.1.1:4444 -> :443   ",
        "172.16.0.1:6666 -> :21     "
    };
    
    const char* actions[] = {
        "ALLOWED",
        "BLOCKED",
        "ALLOWED", 
        "ALLOWED",
        "BLOCKED"
    };
    
    for (int i = 0; i < 5; i++) {
        vga_print("║ ");
        vga_print(connections[i]);
        
        if (strcmp(actions[i], "ALLOWED") == 0) {
            vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        } else {
            vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        }
        
        vga_print(" [");
        vga_print(actions[i]);
        vga_print("]");
        
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        for (int j = strlen(actions[i]); j < 15; j++) vga_print(" ");
        vga_print("║\n");
        
        delay_ms(400);
    }
    
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void ids_monitor(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║              INTRUSION DETECTION SYSTEM                      ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Monitoring network traffic for suspicious activity...       ║\n");
    vga_print("║                                                              ║\n");
    
    const char* alerts[] = {
        "Port scan detected from 192.168.1.200",
        "Multiple failed SSH attempts from 10.0.0.50", 
        "Unusual outbound traffic to known botnet C&C",
        "SQL injection attempt on web application",
        "Potential buffer overflow in service daemon"
    };
    
    const char* severities[] = {
        "MEDIUM",
        "HIGH",
        "CRITICAL",
        "HIGH", 
        "CRITICAL"
    };
    
    for (int i = 0; i < 5; i++) {
        vga_print("║ [");
        
        if (strcmp(severities[i], "CRITICAL") == 0) {
            vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        } else if (strcmp(severities[i], "HIGH") == 0) {
            vga_set_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK);
        } else {
            vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
        }
        
        vga_print(severities[i]);
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("] ");
        vga_print(alerts[i]);
        
        for (int j = strlen(alerts[i]) + strlen(severities[i]); j < 57; j++) {
            vga_print(" ");
        }
        vga_print("║\n");
        
        delay_ms(600);
    }
    
    vga_print("║                                                              ║\n");
    vga_print("║ Total Alerts: 5 | Critical: 2 | High: 2 | Medium: 1        ║\n");
    vga_print("║ Recommended Actions: Block malicious IPs, patch services    ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void memory_dump_analyzer(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                   MEMORY FORENSICS ANALYZER                  ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Analyzing memory dump for forensic artifacts...             ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Memory Layout Analysis:                                      ║\n");
    vga_print("║ • Kernel space: 0x80000000 - 0xFFFFFFFF                     ║\n");
    vga_print("║ • User space:   0x00000000 - 0x7FFFFFFF                     ║\n");
    vga_print("║ • Heap start:   0x00200000                                  ║\n");
    vga_print("║ • Stack top:    0x7FFFEFFF                                  ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Artifacts Found:                                             ║\n");
    vga_print("║ • Deleted file fragments in unallocated space              ║\n");
    vga_print("║ • Network connection traces                                 ║\n");
    vga_print("║ • Encryption keys in process memory                        ║\n");
    vga_print("║ • Malware injection signatures                             ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Hash of analyzed region: ");
    vga_print_hex(0xDEADBEEF);
    vga_print("                         ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void system_integrity_check(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                  SYSTEM INTEGRITY CHECKER                    ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Verifying system file integrity...                          ║\n");
    vga_print("║                                                              ║\n");
    
    const char* files[] = {
        "/kernel/kernel.bin",
        "/boot/bootloader.bin", 
        "/config/system.cfg",
        "/drivers/vga.ko",
        "/drivers/keyboard.ko",
        "/security/firewall.rules"
    };
    
    const uint32_t expected_hashes[] = {
        0xDEADBEEF, 0xCAFEBABE, 0xFEEDFACE,
        0xBAADF00D, 0x8BADF00D, 0xDEADC0DE
    };
    
    for (int i = 0; i < 6; i++) {
        vga_print("║ ");
        vga_print(files[i]);
        for (int j = strlen(files[i]); j < 30; j++) vga_print(" ");
        
        // Simulate hash verification
        uint32_t actual = simple_hash(files[i]);
        if (actual == expected_hashes[i] || i < 4) { // First 4 pass for demo
            vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
            vga_print(" [VERIFIED]   ");
        } else {
            vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
            vga_print(" [MODIFIED]   ");
        }
        
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("║\n");
        delay_ms(200);
    }
    
    vga_print("║                                                              ║\n");
    vga_print("║ Integrity Status: 2 files modified, investigation needed    ║\n");
    vga_print("║ Recommendation: Restore from known good backup              ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void access_control_demo(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                    ACCESS CONTROL DEMO                       ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Demonstrating role-based access control (RBAC)              ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Users and Permissions:                                       ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ admin    - ALL PERMISSIONS                                   ║\n");
    vga_print("║ security - READ_LOGS, SCAN_NETWORK, MANAGE_FIREWALL          ║\n");
    vga_print("║ user     - READ_FILES, EXECUTE_PROGRAMS                      ║\n");
    vga_print("║ guest    - READ_PUBLIC                                       ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Access Attempts:                                             ║\n");
    vga_print("║                                                              ║\n");
    
    const char* attempts[] = {
        "admin -> /etc/shadow",
        "user -> /etc/shadow", 
        "security -> /var/log/auth.log",
        "guest -> /home/user/document.txt",
        "user -> /bin/calculator"
    };
    
    const char* results[] = {
        "GRANTED",
        "DENIED",
        "GRANTED",
        "DENIED", 
        "GRANTED"
    };
    
    for (int i = 0; i < 5; i++) {
        vga_print("║ ");
        vga_print(attempts[i]);
        for (int j = strlen(attempts[i]); j < 35; j++) vga_print(" ");
        
        if (strcmp(results[i], "GRANTED") == 0) {
            vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        } else {
            vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        }
        
        vga_print("[");
        vga_print(results[i]);
        vga_print("]");
        
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        for (int j = strlen(results[i]); j < 15; j++) vga_print(" ");
        vga_print("║\n");
        delay_ms(300);
    }
    
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void log_analyzer(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                      LOG ANALYZER                            ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Analyzing system logs for security events...                ║\n");
    vga_print("║                                                              ║\n");
    
    const char* log_entries[] = {
        "Failed login: user 'admin' from 192.168.1.100",
        "Successful login: user 'john' from 192.168.1.50",
        "Port scan detected from 10.0.0.1",
        "File access denied: /etc/passwd by user 'guest'",
        "Privilege escalation attempt by user 'hacker'"
    };
    
    const char* threat_levels[] = {
        "HIGH",
        "INFO",
        "MEDIUM",
        "LOW",
        "CRITICAL"
    };
    
    for (int i = 0; i < 5; i++) {
        vga_print("║ [");
        
        if (strcmp(threat_levels[i], "CRITICAL") == 0) {
            vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        } else if (strcmp(threat_levels[i], "HIGH") == 0) {
            vga_set_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK);
        } else if (strcmp(threat_levels[i], "MEDIUM") == 0) {
            vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
        } else {
            vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        }
        
        vga_print(threat_levels[i]);
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("] ");
        vga_print(log_entries[i]);
        
        for (int j = strlen(log_entries[i]) + strlen(threat_levels[i]); j < 55; j++) {
            vga_print(" ");
        }
        vga_print("║\n");
        delay_ms(400);
    }
    
    vga_print("║                                                              ║\n");
    vga_print("║ Summary: 1 Critical, 1 High, 1 Medium, 1 Low, 1 Info       ║\n");
    vga_print("║ Action Required: Investigate privilege escalation attempt   ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}

void file_recovery_simulator(void) {
    vga_print("\n╔══════════════════════════════════════════════════════════════╗\n");
    vga_print("║                   FILE RECOVERY SIMULATOR                    ║\n");
    vga_print("╠══════════════════════════════════════════════════════════════╣\n");
    vga_print("║ Scanning unallocated disk space for deleted files...        ║\n");
    vga_print("║                                                              ║\n");
    
    const char* recovered_files[] = {
        "document.txt (1.2KB) - Recoverable",
        "password.docx (45KB) - Partially recoverable", 
        "financial.xlsx (234KB) - Corrupted",
        "photo.jpg (2.1MB) - Recoverable",
        "database.sql (15MB) - Overwritten"
    };
    
    for (int i = 0; i < 5; i++) {
        vga_print("║ Found: ");
        vga_print(recovered_files[i]);
        for (int j = strlen(recovered_files[i]); j < 48; j++) vga_print(" ");
        vga_print("║\n");
        delay_ms(500);
    }
    
    vga_print("║                                                              ║\n");
    vga_print("║ Recovery Statistics:                                         ║\n");
    vga_print("║ • Files found: 5                                            ║\n");
    vga_print("║ • Fully recoverable: 2                                      ║\n");
    vga_print("║ • Partially recoverable: 1                                  ║\n");
    vga_print("║ • Corrupted/Overwritten: 2                                  ║\n");
    vga_print("║                                                              ║\n");
    vga_print("║ Note: Recovery success depends on disk activity since       ║\n");
    vga_print("║ deletion. Use write-blocking tools in real forensics.       ║\n");
    vga_print("╚══════════════════════════════════════════════════════════════╝\n");
}
