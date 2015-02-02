#!/usr/bin/env python

import ROOT

f = ROOT.TFile("~/Development/ttree/treesTTBar_DM600_v2.root")
t = f.DMTreesDumper.Get('ttDM600__noSyst')

l = t.GetLeaf("jetE")

t.Scan("jetE:elE:Iteration$","","",1)
t.GetEntry(0)

for b in t.GetListOfBranches():
    print b.GetName(),t.GetBranchStatus(b.GetName())

print l.GetName()
print l.GetTypeName()
print l.GetLen()
print l.GetValue()
