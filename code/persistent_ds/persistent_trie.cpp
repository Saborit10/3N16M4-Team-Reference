/* Trie Persistente

 - L: max length of a word
 - S: size of alphabet
 - W: # of words
    
 - Use example:
    string k = "ale", v = "single";
    int r = wadd(0, k, v);
    v = "in a relationship";
    r = wadd(r, k, v);
    cout << qry(r, k) << endl;
   
 - WARNING: Tries are too memory consuming, be careful.
 - Memory: O(L*S*W)
 - Time: wadd - O(L), qry - O(L) 
*/

#define sz(X) (X).size() 

/* Represents a node in the trie */
struct node
{
  map<char, int> ch;
  string val="";
  node(){}
}nullTrie;

vector<node> t{nullTrie}; // nodes (our RAM)

/* Adds a key 'key' with a value 'val'
 * x should be a root */
int wadd(int x, string& key, string& val)
{
  int r = sz(t);
  t.pb(t[x]);
  int s = r;
  for(char c: key)
  {
    if(t[s].ch.count(c)) t.pb(t[t[s].ch[c]]);
    else t.pb(nullTrie);
    t[s].ch[c] = sz(t) - 1;
    s = t[s].ch[c];
  }
  t[s].val = val;
  return r;
}

/* For a given root (timeline) what value stores the key 'key' */
string qry(int s, string& key)
{
  for(char c: key)
  {
    if(t[s].ch.count(c)) s = t[s].ch[c];
    else return string("N/A");
  }
  return t[s].val==""?string("N/A"):t[s].val;
}
