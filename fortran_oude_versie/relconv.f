      SUBROUTINE RELCONV(N,W)
      INTEGER N
      REAL W
      VECTOR FX
      VECTOR GX
      VECTOR XX
      VECTOR RESX
      INTEGER I,J,K,L
      REAL LF,XF,XR,XW,XS,WID
      IF(W.GE.1.0) THEN
      PRINT *,'Resolution is ',W,' channels everywhere'
      ELSEIF(W.GT.0.) THEN
      PRINT *,'Resolution is ',100*W,'% everywhere'
      ELSE
      PRINT *,'Resolution is given by RESX vector'
      ENDIF
      DO I=1,N
      GX(I)=0.0
      ENDDO
      DO I=1,N
* WID is the WIDTH in CHANNELS
      IF(W.GE.1.0) THEN
      WID = W
      ELSEIF(W.GT.0.) THEN
      WID = W * I
      ELSE
      WID = RESX(I)
      ENDIF
      L   = 4. * WID
      IF ( L.LE.0 ) L = 1
c loop over region around X
      DO J=-L,L
        XG = J
c XW (weight) is value of gaussian at XG
        XW = (1./sqrt(6.2832))*exp(-0.5*(XG/WID)**2)/WID
c convolution
        K=I+J
	IF((K.GE.1).AND.(K.LE.N)) GX(K)=GX(K)+FX(I)*XW
      ENDDO
* LOOP OVER J
      ENDDO
* LOOP OVER I
      RETURN
      END
