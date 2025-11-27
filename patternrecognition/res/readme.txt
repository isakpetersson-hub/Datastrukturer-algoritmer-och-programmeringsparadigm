/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150      0,018s        0,009s
    200      0,039s        0,014s
    300      0,098s        0,025s
    400      0,213s        0,043s
    800      1,788s        0,139s
   1600      13,100s       0,545s
   3200      104,822s      2,120s
   6400      838,576s(e)   8,962s
  12800      6708,608s(e)  39,219s


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n⁴) Koden tester alla komibinationer av 4st punkter

Sortering: O(n²log(n)) Itererar två gånger över allt och sorterar vilket ger log(n)
