### gsm sms relay control system (arduino nano + sim900a)

this project is a simple gsm-based home automation system using an arduino nano and a sim900a module. it allows you to control a relay using sms commands from your mobile phone.

---

## components used

- arduino nano  
- sim900a gsm module  
- 4-channel relay module  
- 5v power supply (stable)  
- jumper wires  
- sim card with sms balance  

---

## working

1. user sends sms to the sim inside sim900a  
2. sim900a receives the message  
3. arduino reads the sms via serial communication  
4. based on the command:
   - "ON" → relay turns ON  
   - "OFF" → relay turns OFF  
5. arduino optionally sends confirmation sms back  

---

## wiring

### sim900a to arduino nano

- tx → d10  
- rx → d11  
- vcc → 5v (stable external supply)  
- gnd → gnd (common ground)  

### relay to arduino nano

- in → d7  
- vcc → 5v  
- gnd → gnd  

---

## sms commands

- `ON` → turns relay ON  
- `OFF` → turns relay OFF  

(optional)
- system can send confirmation sms back to user

---

### features

- gsm-based remote control (no wifi needed)  
- simple sms command system  
- relay control for appliances  
- optional auto reply system  

---

### important notes

- use a stable 5v power supply (minimum 2a recommended for sim900a)  
- ensure sim card has sms service and network signal  

---
