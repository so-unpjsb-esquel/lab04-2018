int
sys_pgcnt(void)
{
    pde_t *pde;  // page directory
    pte_t *pte;  // page table

    int i = 0;
    int j = 0;
    int cnt = 0;

    unsigned int flag = PTE_P | PTE_U;

    // NPDENTRIES indica el número de entradas en cada page directory (1024)    
    for(i=0; i < NPDENTRIES; i++) {
        
        // proc->pgdir es un puntero al directorio de paginas
        // se recupera la i-esima entrada
        pde = &((proc->pgdir)[i]);

        // si el bit PTE_P es igual a 1, entonces es una entrada valida
        if(*pde & PTE_P) {
            
            // PTE_ADDR hace pde & ~0xFFF
            // p2v hace (pde & ~0xFFF) + KERNBASE
            // Lo casteamos a pte_t*
            pte = (pte_t*) P2V(PTE_ADDR(*pde));
            
            // NPTENTRIES indica el número de entradas en cada page table (1024)
            for(j=0; j < NPTENTRIES; j++) {                
                // chequeamos si el bit PTE_P | PTE_U esta presente
                if((pte[j] & flag) == flag) {                   
                   cnt = cnt + 1;
                }
            }
        }  
    }

    return cnt;
}