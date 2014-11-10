      real function compfree(x)
      real x, compton
      vector edens(1)
      if(edens(1).eq.0) edens(1)=3.37e23
      compton=compscat(0,x)*edens(1)*1e-24
      compfree=1/compton
      return
      end

include 'compscat.f'
