#!/usr/bin/env python3
import sys

def parse(path):
    data = {}
    section = None
    with open(path) as f:
        for line in f:
            line = line.rstrip()
            if line.startswith("=== "):
                section = line.strip("= ").strip()
                data[section] = []
            elif section and line and not line.startswith("#"):
                parts = line.split()
                if not parts or parts[0] == "key":
                    continue
                if len(parts) >= 4:
                    try:
                        data[section].append((parts[0], float(parts[-1])))
                    except ValueError:
                        pass
    return data

def main():
    if len(sys.argv) != 3:
        print("usage: compare.py glibc.txt hmalloc.txt", file=sys.stderr)
        sys.exit(1)

    g = parse(sys.argv[1])
    h = parse(sys.argv[2])

    print(f"{'section':<28} {'key':<12} {'glibc(ns)':>12} {'hmalloc(ns)':>13} {'ratio':>8}")
    print("-" * 80)
    for section in g:
        if section not in h:
            continue
        hmap = dict(h[section])
        for k, vg in g[section]:
            if k not in hmap:
                continue
            vh = hmap[k]
            ratio = vh / vg if vg > 0 else float('inf')
            flag = "  <-- SLOW" if ratio > 1.5 else ("  <-- FAST" if ratio < 0.7 else "")
            print(f"{section:<28} {k:<12} {vg:>12.2f} {vh:>13.2f} {ratio:>8.2f}{flag}")

if __name__ == "__main__":
    main()
