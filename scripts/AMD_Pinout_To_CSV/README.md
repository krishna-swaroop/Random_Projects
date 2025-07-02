
# 🧩 Zynq Ultrascale+ Pinout CSV Generator

This script (`symbol_parser_v3.py`) processes the ASCII pinout text file for AMD Zynq UltraScale+ device (Pinout Files provided on AMD Technical Information Portal) and generates a CSV file formatted for symbol creation in EDA tools such as Altium Designer.  
While creating a new symbol in Altium, the user can use the Smart Paste utility to directly import the pins.  
In KiCAD, copy-paste the CSV into the Bulk Editing Window.

---

## 📂 File Structure

```
.
├── symbol_parser_v3.py                      # Main parser script
├── XCZU19EG-L1FFVC1760I.txt                 # Input: Example Xilinx ASCII pinout file
└── zynq_altium_symbol_by_bank.csv           # Output: CSV sorted by IO banks
```

---

## ⚙️ What It Does

The script performs the following tasks:

1. **Parses** the provided Xilinx pinout text file
2. **Extracts**:
   - Pin number
   - Pin name
   - IO bank association
3. **Classifies pins** into electrical types using heuristics:
   - `"VCC"`, `"GND"`, `"VP"`, `"VN"` → `Power`
   - `"CLK"`, `"REF"` → `Input`
   - `"IO_"`, `"MGT"` → `I/O`
   - `"NC"` → `NC`
4. **Groups pins by IO Bank** (e.g., `BANK_64`, `BANK_65`)
5. **Outputs a clean CSV** with the following format:

---

### ✅ Sample CSV Output

```csv
Designator,Name,Electrical Type,Group
A23,IO_L24N_T3U_N11_71,I/O,BANK_71
B23,IO_L24P_T3U_N10_71,I/O,BANK_71
Y20,VCCADC,Power,BANK_NA
...
```

---

## 🧪 How to Use

### 🐍 Step 1: Run the script

```bash
python symbol_parser_v3.py
```

This will read from `XCZU19EG-L1FFVC1760I.txt` and write the file `zynq_altium_symbol_by_bank.csv` in the same directory.

---

## 📌 Notes

- The script is **customized for Zynq UltraScale+** devices.
- Other FPGAs might need adjustments to the parsing logic (e.g., line structure).
- No third-party libraries are required—this uses Python’s built-in `csv` module.
- If you need symbol generation based on other sorting strategies, modify the grouping section accordingly.

---

## 🛠 Dependencies

- Python 3.x
- No external dependencies

---

## 📇 Credits

- ASCII Pinout File: Xilinx, Inc.
- Author: Krishna Swaroop Dhulipalla
- Script: `symbol_parser_v3.py`

---
