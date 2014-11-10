      REAL FUNCTION EPOW(X)
      COMMON/PAWPAR/PAR(2)
      EPOW=PAR(1)*(x**(PAR(2)))
      END
