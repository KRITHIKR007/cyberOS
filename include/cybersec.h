#ifndef CYBERSEC_H
#define CYBERSEC_H

#include <stdint.h>
#include <stddef.h>

// Network security
void network_scanner(void);
void port_scanner(const char* target);
void firewall_simulator(void);

// Cryptography
void hash_generator(const char* input, const char* algorithm);
void password_analyzer(const char* password);
void encryption_tool(const char* text, const char* key);
void decryption_tool(const char* ciphertext, const char* key);

// System security
void vulnerability_scanner(void);
void system_integrity_check(void);
void access_control_demo(void);

// Forensics
void memory_dump_analyzer(void);
void file_recovery_simulator(void);
void log_analyzer(void);

// Intrusion detection
void ids_monitor(void);
void anomaly_detector(void);
void threat_intelligence(void);

// Security utilities
uint32_t simple_hash(const char* data);
uint32_t crc32_hash(const char* data, size_t len);
int password_strength_score(const char* password);
void generate_secure_password(char* buffer, size_t length);

#endif
