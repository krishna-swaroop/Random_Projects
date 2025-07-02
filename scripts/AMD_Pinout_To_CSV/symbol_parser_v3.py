import csv

INPUT_FILE = "XCZU19EG-L1FFVC1760I.txt"
OUTPUT_FILE = "zynq_altium_symbol_by_bank.csv"

def infer_electrical_type(pinname):
    name = pinname.upper()
    if "GND" in name or "GNDADC" in name:
        return "Power"
    if "VCC" in name or "VREF" in name or "VP" in name or "VN" in name:
        return "Power"
    if name == "NC":
        return "NC"
    if "IO_" in name or "MGT" in name:
        return "I/O"
    if "CLK" in name or "REF" in name:
        return "Input"
    return "I/O"

def parse_pinout():
    pins = []
    start_reading = False

    with open(INPUT_FILE, "r") as file:
        for line in file:
            if line.startswith("Pin") and "Pin Name" in line:
                start_reading = True
                continue
            if not start_reading or line.startswith("--") or not line.strip():
                continue

            pin = line[0:6].strip()
            name = line[6:40].strip()
            bank_raw = line[60:66].strip()

            if pin and name:
                etype = infer_electrical_type(name)
                group = f"BANK_{bank_raw}" if bank_raw else "BANK_NA"
                pins.append((group, pin, name, etype))

    # Sort numerically by bank (extract digits), then by pin
    def bank_sort_key(x):
        group = x[0]
        if group.startswith("BANK_"):
            try:
                return (int(group[5:]), x[1])
            except ValueError:
                return (9999, x[1])
        return (9999, x[1])

    return sorted(pins, key=bank_sort_key)

def write_csv(pins):
    with open(OUTPUT_FILE, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["Designator", "Name", "Electrical Type", "Group"])
        for group, pin, name, etype in pins:
            writer.writerow([pin, name, etype, group])

if __name__ == "__main__":
    pins = parse_pinout()
    write_csv(pins)
    print(f"✅ Exported sorted pin list to {OUTPUT_FILE}")
