C-Compiler-Setup
================

Programs related to creating a C compiler.

Current Changes:
    HashTables declared not as pointer are technically a memory leak.  Since we
    never created them anywhere but main it shouldn't have been a problem, but we
    should be consistent.
    
    We can't reference the CAPACITY const, because our hashtable will keep changing size.
    * Probably the source of many seg faults.
    * So I removed the reference to it in the hash() function, but we still want
        to % by the h->length, so either you pass that in to the function or
        modulo it after it returns (The latter is chosen as to not change
        the function signiture.)
    
    Resize method created.  When we resize a hashtable unlike an array, the hash of
    the values actually changes beacuse it position in the array is hash % h->length,
    so that means we actually need to create a second hashtable and reinsert all our
    values.  But it comes down to one thing, either make an immutable hashfunction
    or recalculate hash values(we can recalculate cleverly by storing information about
    the original hash, but that is just more complicated, and I am not sure it would
    have provided a lot of benefit.)
    
    int update_length(unsigned int); Function has been removed, as you cannot just
    change the length without also recalculating hashes for every element.
