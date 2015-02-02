#!/usr/bin/env python

import ROOT

f = ROOT.TFile('~/Development/ttree/treesTTBar_DM600_v2.root')
t = f.DMTreesDumper.Get('ttDM600__noSyst')
entries = t.GetEntries()

# f0 = ROOT.TFile('~/Development/ttree/treesTTBar_DM600_v2_X.root','recreate')
# f0.mkdir('DMTreesDumper')
# t0 = t.CloneTree()
# f0.Save()
# f0.Close()

last1 = entries/2
print 'Copying',last1,'/',entries,'entries'
f1 = ROOT.TFile('~/Development/ttree/treesTTBar_DM600_v2_A.root','recreate')
f1.mkdir('DMTreesDumper').cd()
t1 = t.CopyTree('','',last1, 0)
f1.Save()
f1.Close()

print 'Copying',(entries-last1),'/',entries,'entries'
f2 = ROOT.TFile('~/Development/ttree/treesTTBar_DM600_v2_B.root','recreate')
f2.mkdir('DMTreesDumper').cd()
t2 = t.CopyTree('','',last1)
f2.Save()
f2.Close()
