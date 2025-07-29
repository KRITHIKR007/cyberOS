# CyberOS Visual Preview

## Boot Screen
```
CyberOS Bootloader v1.0
Loading kernel...
```

## Main Operating System Interface
```
Welcome to CyberOS!
A simple operating system for learning.

Available commands:
  help    - Show this help
  clear   - Clear screen
  info    - System information
  halt    - Shutdown system

cyberos> _
```

## When you type 'help':
```
cyberos> help

Available commands:
  help    - Show this help
  clear   - Clear screen
  info    - System information
  halt    - Shutdown system
cyberos> _
```

## When you type 'info':
```
cyberos> info

CyberOS v1.0
A simple x86 operating system
Built for educational purposes
Memory: Basic management
Display: VGA text mode 80x25
cyberos> _
```

## When you type 'clear':
The screen clears and shows:
```
cyberos> _
```

## When you type 'halt':
```
cyberos> halt

Shutting down CyberOS...
It's now safe to turn off your computer.
```

## Visual Features:
- Green text on black background (classic terminal look)
- 80 columns x 25 rows text mode
- Real-time keyboard input with echo
- Backspace support
- Command history in buffer
- Scrolling when screen fills up

## Color Scheme:
- Background: Black
- Text: Light Green (classic hacker/terminal aesthetic)
- Prompt: Same green color
- All text is monospaced for clean appearance
