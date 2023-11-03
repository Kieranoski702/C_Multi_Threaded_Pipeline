#!/usr/bin/env bash

# Run on lab pc or install pandoc and tex-live (linux) / mactex (mac)

pandoc -t pdf                        \
       -o report.pdf                 \
       --resource-path=.:figures     \
       --standalone                  \
       --toc                         \
       --toc-depth=2                 \
       --citeproc                    \
       --bibliography=references.bib \
       --csl=ieee.csl                \
       report.md
