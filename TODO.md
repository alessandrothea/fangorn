TODOS
=====

 * Create a TTreeAnalyzer class
 * TTreeAnalyzer must store TLeafReader classes
 * TLeaf are read only
 * TBranch::SetBranchAddress is needed if write access is required.
 * Remeber that 
   * TLeaf holds a very nice set of infos
   * But it requires being updated if the file changes in a TChain
   * No write access (need some other trick to write to new branches) 
 * Ingredients required
   *  A Analyzer + BranchProxy class, entangled together. Analyzer holds a list of branch proxies.
   *  BranchProxy points to a Leaf. It holds the pointer to the buffer. SetBranchAddress is called on the buffer pointer. TChain takes care of updating the branches when new files are opened. No other action is required
   *  A LeafHandle class to provide user access: 
   ```
LeafHandle<Float_t> f = a->getHandle<Float_t>(name)
std::cout << f+1 << std::endl;
std::cout << f[2] << std::endl;
```
