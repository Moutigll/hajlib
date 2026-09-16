#!/usr/bin/env python3
"""Generate a bar plot comparing two benchmark results.
Usage:
	python3 bench_plot.py glibc.txt hmalloc.txt
"""
import sys, matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from compare import parse

def main():
    g = parse(sys.argv[1])
    h = parse(sys.argv[2])

    sections = [s for s in g if s in h]
    fig, axes = plt.subplots(1, len(sections), figsize=(4 * len(sections), 4))
    if len(sections) == 1:
        axes = [axes]

    for ax, section in zip(axes, sections):
        keys = [k for k, _ in g[section]]
        vg = [v for _, v in g[section]]
        vh = [v for _, v in h[section]]
        x = range(len(keys))
        ax.bar([i - 0.2 for i in x], vg, width=0.4, label="glibc")
        ax.bar([i + 0.2 for i in x], vh, width=0.4, label="hmalloc")
        ax.set_xticks(list(x))
        ax.set_xticklabels(keys, rotation=45, ha="right")
        ax.set_title(section)
        ax.set_ylabel("ns/op")
        ax.legend()
        ax.grid(True, axis="y", alpha=0.3)

    plt.tight_layout()
    plt.savefig("bench.png", dpi=120)
    print("wrote bench.png")

if __name__ == "__main__":
    main()
