#include "calculator.h"
#include "string.h"
#include "vga.h"

// Simple recursive descent parser for basic arithmetic
static const char* expr_ptr;

static int32_t parse_number(void);
static int32_t parse_factor(void);
static int32_t parse_term(void);
static int32_t parse_expression(void);

static void skip_whitespace(void) {
    while (*expr_ptr == ' ' || *expr_ptr == '\t') {
        expr_ptr++;
    }
}

static int32_t parse_number(void) {
    skip_whitespace();
    
    int32_t result = 0;
    int negative = 0;
    
    if (*expr_ptr == '-') {
        negative = 1;
        expr_ptr++;
    } else if (*expr_ptr == '+') {
        expr_ptr++;
    }
    
    while (*expr_ptr >= '0' && *expr_ptr <= '9') {
        result = result * 10 + (*expr_ptr - '0');
        expr_ptr++;
    }
    
    return negative ? -result : result;
}

static int32_t parse_factor(void) {
    skip_whitespace();
    
    if (*expr_ptr == '(') {
        expr_ptr++; // Skip '('
        int32_t result = parse_expression();
        skip_whitespace();
        if (*expr_ptr == ')') {
            expr_ptr++; // Skip ')'
        }
        return result;
    }
    
    return parse_number();
}

static int32_t parse_term(void) {
    int32_t result = parse_factor();
    
    while (1) {
        skip_whitespace();
        
        if (*expr_ptr == '*') {
            expr_ptr++;
            result *= parse_factor();
        } else if (*expr_ptr == '/') {
            expr_ptr++;
            int32_t divisor = parse_factor();
            if (divisor != 0) {
                result /= divisor;
            } else {
                return 0; // Division by zero
            }
        } else if (*expr_ptr == '%') {
            expr_ptr++;
            int32_t divisor = parse_factor();
            if (divisor != 0) {
                result %= divisor;
            } else {
                return 0; // Division by zero
            }
        } else {
            break;
        }
    }
    
    return result;
}

static int32_t parse_expression(void) {
    int32_t result = parse_term();
    
    while (1) {
        skip_whitespace();
        
        if (*expr_ptr == '+') {
            expr_ptr++;
            result += parse_term();
        } else if (*expr_ptr == '-') {
            expr_ptr++;
            result -= parse_term();
        } else {
            break;
        }
    }
    
    return result;
}

int32_t evaluate_expression(const char* expr) {
    expr_ptr = expr;
    return parse_expression();
}

void print_calculator_help(void) {
    vga_print("\nCalculator Help:\n");
    vga_print("Supported operations:\n");
    vga_print("  +  Addition\n");
    vga_print("  -  Subtraction\n");
    vga_print("  *  Multiplication\n");
    vga_print("  /  Division\n");
    vga_print("  %  Modulus\n");
    vga_print("  () Parentheses\n");
    vga_print("\nExamples:\n");
    vga_print("  calc 2 + 3\n");
    vga_print("  calc (5 * 6) / 2\n");
    vga_print("  calc 100 % 7\n");
}
