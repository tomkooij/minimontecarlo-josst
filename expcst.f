      REAL FUNCTION EXPCST(X)
      COMMON/PAWPAR/PAR(3)
      EXPCST=PAR(1)+EXP(PAR(2)+PAR(3)*X)
      END

