
FREQ=16000000
BR=110000
TWPS=3

# für 1MHz bei 16MHz
# TWPS=1  TWBR=0

# für 200KHz bei 16MHz
# TWPS=2  TWBR=2






#$BR=$FREQ/(16 + 2*PWBR * 4^TWPS)
#
#$BR * (16 + 2*PWBR * 4^TWPS)= $FREQ
#
#16*$BR + $BR * 2*$PWBR * 4^$TWPS = $FREQ
#
#$BR * 2*$PWBR * 4^$TWPS = $FREQ - 16*$BR
#
#$PWBR * 4^$TWPS = ($FREQ - 16* $BR) / (2$BR)
#
CALC="scale=2;(($FREQ - 16*$BR) / (2*$BR)) / 4^$TWPS"
echo $CALC
TWBR=`echo $CALC | bc`
echo $TWBR




#  3 Baudrate auf 400kHz setzen
#  4 TWPS = letzte 2 Bit aus TWSR
#  5 TWPS (Prescaler) auf 0
#  6 Baudrate = FREQ / ( 16 + 2(PWBR) * 4^TWPS)
#  7 400000 = 16000000 / ( 16 + 2(PWBR) )
#  8 400000 * 16 + 400000 * 2PWBR = 16000000
#  9 640000 + 800000 * PWBR = 16000000
# 10 80000 PWBR = 9600000
# 11 PWBR = 12

