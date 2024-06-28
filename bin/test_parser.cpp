#include <gtest/gtest.h>
#include "parser.cpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp> 
#define DETERMINE_TYPE_TEST(TESTNAME, TOKEN, TOKEN_TYPE) TEST(DetermineType, TESTNAME){ \
  string token = TOKEN; \
  string type = determine_type(TOKEN); \
  ASSERT_EQ(type, #TOKEN_TYPE); \
}
#define PARSER_TEST(TESTNAME, STRING) TEST(Parser, TESTNAME){\
  Parser p;\
  string s = STRING;\
  vector<string> expr;\
  boost::split(expr, s, boost::is_any_of(" "));\
  p.parse(expr);\
  string res = recreate_expression(p.expr_trees[0]);\
  ASSERT_EQ(s, res);\
}

#define SUB_TYPE(a,b) else if(root->type == b){res += a;}

void inOrderTraversal(ExprTreeNode* root, string& res){
  if(!root){
    return;
  }
  if((root->left) || (root->right)){
    res += "( ";
  }
  inOrderTraversal(root->left, res);
  if(root->left){
    res += " ";
  }
  if(root->type == "VAL"){
    res += to_string(root->num);
  }
  else if(root->type == "VAR"){
    res += root->id;
  }
  else{
  if(root->type == "ADD"){
    res  += "+";
  }
    SUB_TYPE("-", "SUB")
    SUB_TYPE("*", "MUL")
    SUB_TYPE("/", "DIV")
    SUB_TYPE(":=", "ASSIGN")
    SUB_TYPE("ret", "RET")
    SUB_TYPE("del", "DEL")
    SUB_TYPE("(", "LB")
    SUB_TYPE(")", "RB")
  }
  if(root->right){
    res += " ";
  }
  inOrderTraversal(root->right, res);
  if((root->left) || (root->right)){
    res += " )";
  }
}
string recreate_expression(ExprTreeNode* root){
  string res;
  inOrderTraversal(root, res);
  res.erase(0,2);
  res.pop_back();
  res.pop_back();
  return res;
}


DETERMINE_TYPE_TEST(Number, "23409382", VAL);
DETERMINE_TYPE_TEST(NegativeNumber, "-230989", VAL);
DETERMINE_TYPE_TEST(Addition, "+", ADD);
DETERMINE_TYPE_TEST(Subtraction, "-", SUB);
DETERMINE_TYPE_TEST(Multiplication, "*", MUL);
DETERMINE_TYPE_TEST(BracketRight, ")", RB);
DETERMINE_TYPE_TEST(BracketLeft, "(", LB);
DETERMINE_TYPE_TEST(Delete, "del", DEL);
DETERMINE_TYPE_TEST(Return, "ret", RET);
DETERMINE_TYPE_TEST(Assign, ":=", ASSIGN);
DETERMINE_TYPE_TEST(VariableBasic, "aviral", VAR);
DETERMINE_TYPE_TEST(Variable1, "_viral", VAR);
DETERMINE_TYPE_TEST(Variable2, "v_iral", VAR);

PARSER_TEST(BasicTest, "v := ( 4 + 5 )");
PARSER_TEST(SingleTest, "v := 4");
PARSER_TEST(NegativeTest, "v := ( -4 + 5 )");
PARSER_TEST(NegativeNegativeTest, "v := ( -4 + -5 )");
PARSER_TEST(RetTest, "ret := ( ( 3 / 5 ) + 5 )");
PARSER_TEST(DelTest, "del := ( ( k / 5 ) + ( 3 - 8 ) )");
PARSER_TEST(MultiLengthTest, "v := ( aslsda + ( 23094 + 32409 ) )")

PARSER_TEST(UltimateTest, "v := ( ( ( ( ( ( ( ( ( ( 650409 + Ge ) + ( 132880 * 431907 ) ) - ( ( peYFBAn / 10678 ) - ( JJKsffd * hnm ) ) ) / ( ( ( 572108 / 181611 ) - ( EzQF * 8289 ) ) - ( ( 832654 - 592310 ) / ( 826642 - oAtUbgErz ) ) ) ) / ( ( ( ( 597763 / 116619 ) + ( B + 718540 ) ) + ( ( -1309 + ebjcV ) * ( -95529 / EzXoV ) ) ) / ( ( ( 676909 - 928084 ) / ( RvY + 176007 ) ) - ( ( 636693 / ZQk ) / ( eoZ / h ) ) ) ) ) - ( ( ( ( ( fDtkzKn - VVreKnw ) + ( 468172 - xEOu ) ) + ( ( kmkmWf - Mf ) * ( GG * AnS ) ) ) - ( ( ( 275370 / DqITgEDv ) / ( YpJbdJAoW - hISL ) ) * ( ( ClmlUpLg - 668696 ) * ( 13837 / fFNzq ) ) ) ) + ( ( ( ( 976569 - 751821 ) / ( 894343 * VzH ) ) * ( ( aU - 879444 ) - ( 668190 * hZnjR ) ) ) - ( ( ( kcJZQnpv - 850223 ) * ( 566373 * aeKFcADOV ) ) - ( ( 278325 / 442417 ) - ( 16851 + dvRckXG ) ) ) ) ) ) + ( ( ( ( ( ( s * jWdcRTR ) + ( 772854 * 644864 ) ) / ( ( -64851 * 45624 ) + ( 99641 / NhnHxlVSM ) ) ) - ( ( ( 275814 - 856073 ) + ( rVUzUyy / tmRx ) ) - ( ( 329767 - heh ) + ( rP - 781872 ) ) ) ) + ( ( ( ( 666033 / IDLFB ) - ( ZpsiXJO - 968533 ) ) / ( ( 487763 * 953836 ) * ( NtPoZONj + gv ) ) ) * ( ( ( dsYB * s ) / ( kmKzt / 926546 ) ) / ( ( 137506 + G ) + ( dpUFISYBL - plT ) ) ) ) ) - ( ( ( ( ( -75820 / eSaWecHx ) - ( dwCKdoeqn + 500279 ) ) + ( ( 417619 + 666241 ) * ( C - fSF ) ) ) + ( ( ( 65239 - YBhpQk ) * ( 315455 * 40694 ) ) * ( ( uG / k ) - ( -21520 / 940233 ) ) ) ) + ( ( ( ( 369644 - K ) / ( QXElHVnAQ / uoRDTew ) ) * ( ( 581601 + nvLWiT ) / ( 111616 + TFeBrdJe ) ) ) + ( ( ( 595089 - 289246 ) + ( cu + 426068 ) ) * ( ( BE / TLHZC ) / ( 842865 * 814839 ) ) ) ) ) ) ) - ( ( ( ( ( ( ( 30472 + sEIjKZj ) + ( doWOZHc * 547025 ) ) / ( ( 633264 - 134788 ) - ( RJfB + 146699 ) ) ) / ( ( ( xI - 915921 ) - ( 238582 - 497541 ) ) - ( ( mIvJ / CSlWyS ) - ( mwmYuSVSY + S ) ) ) ) * ( ( ( ( RHKEod - 995966 ) / ( 736852 / 48387 ) ) * ( ( 491744 + 957693 ) / ( fmJgutwY + 917686 ) ) ) + ( ( ( 3314 / -91081 ) / ( 582841 + 13100 ) ) * ( ( Fu + 524839 ) + ( ePCoHrnJ * 324718 ) ) ) ) ) + ( ( ( ( ( 712430 / 410484 ) - ( Stf + 21414 ) ) / ( ( SV + 136261 ) + ( pCB - 18279 ) ) ) + ( ( ( MYl * 519104 ) / ( VcBwpURmf * 109111 ) ) + ( ( FAoWj + 191853 ) - ( 202146 + 224986 ) ) ) ) / ( ( ( ( 527228 * tTzFenh ) * ( zPnBTKdGC + Dju ) ) * ( ( dihA / QsFWzDdW ) - ( 625292 - 726549 ) ) ) + ( ( ( apaB / bic ) * ( -95860 + mMmTk ) ) / ( ( 901416 * WCAWR ) - ( 200657 + 524827 ) ) ) ) ) ) * ( ( ( ( ( ( YlZKhAb / gaJieXYP ) * ( 16219 / vnGGgzs ) ) + ( ( PBo + 347901 ) * ( 605152 * qpW ) ) ) * ( ( ( OWkm - KdtfWSZg ) / ( c + Wfqa ) ) * ( ( AapmTCSWp * vGSUypZXN ) * ( AXheb - vDWgHKGB ) ) ) ) - ( ( ( ( 122012 * 917560 ) / ( tqmUPdxtR * OXl ) ) * ( ( 113213 - 985981 ) * ( XUEi - t ) ) ) - ( ( ( 906960 + s ) + ( 423465 + -2194 ) ) - ( ( 75029 + -48079 ) * ( bdXyxYWN + fbXP ) ) ) ) ) + ( ( ( ( ( h - VhxR ) + ( 182205 / lsgJlpy ) ) + ( ( 704022 / 992540 ) / ( 223015 + ZIRPjySz ) ) ) + ( ( ( 84124 * LqI ) + ( fVDYhJp + 292480 ) ) * ( ( t + 246923 ) / ( 214932 * UTNLZ ) ) ) ) + ( ( ( ( -5931 * 891661 ) / ( NvMDj * IEKyLWL ) ) * ( ( 226022 - 322648 ) - ( tjW * hxfpubIet ) ) ) * ( ( ( 248048 * BVdAOik ) * ( 539680 * 507209 ) ) - ( ( 796428 * Lsfbr ) + ( 160530 * 297109 ) ) ) ) ) ) ) ) / ( ( ( ( ( ( ( ( tcc * avz ) / ( pcQuP / ay ) ) * ( ( 490917 - 584725 ) + ( 879615 / 423121 ) ) ) * ( ( ( 928855 - 967855 ) - ( 476749 * 67171 ) ) * ( ( AsywOSgW + 867031 ) * ( ym + 876333 ) ) ) ) + ( ( ( ( 208075 - 663646 ) - ( IX * 322788 ) ) * ( ( SsklcBALI * 75825 ) / ( 272504 * -25740 ) ) ) + ( ( ( JrHjdbvtn - PD ) * ( QltYYLfg + U ) ) * ( ( lnSE - 244205 ) * ( Lvc * -48213 ) ) ) ) ) / ( ( ( ( ( ypfnfKg * 8051 ) + ( vhq - jcyIA ) ) / ( ( BiuoG + GsaGHZX ) * ( ktBzXZed * QOqwvivm ) ) ) - ( ( ( T - sK ) * ( ftL * -77966 ) ) * ( ( PzKUvW + 960563 ) - ( rz + 11641 ) ) ) ) - ( ( ( ( 818873 + JQW ) * ( 819563 * 589475 ) ) / ( ( RBq * blMNzamw ) + ( KRh - 242319 ) ) ) + ( ( ( 37929 + 27906 ) - ( T - h ) ) + ( ( AdyVrs - 861005 ) - ( 997739 / eViVhH ) ) ) ) ) ) - ( ( ( ( ( ( rkdpDOgOk + ttDW ) + ( q - 628013 ) ) / ( ( ttLVEH / wfzbAijH ) * ( 961594 - 904882 ) ) ) * ( ( ( ImpRtJu + skNs ) * ( L + ZsyYcPoFD ) ) / ( ( A * ilYFZT ) / ( -51798 - 999893 ) ) ) ) + ( ( ( ( HlomRE - 930635 ) / ( 789364 + 399221 ) ) + ( ( 752447 - 194136 ) * ( fhkd / 584303 ) ) ) - ( ( ( GtNTi + 431879 ) / ( 409412 * jCK ) ) / ( ( 965097 * ACmXduT ) * ( nQx / WeNzMqN ) ) ) ) ) / ( ( ( ( ( WZdomr + AxfhJeglP ) * ( 132837 / 549904 ) ) * ( ( SWilxqDb / UgQyET ) - ( MyXcuoX / ZwpxXy ) ) ) + ( ( ( 63588 * QzX ) / ( fDDZFVKz - 574502 ) ) * ( ( 904857 * iWdQh ) / ( zTimJ + 949898 ) ) ) ) * ( ( ( ( -463 * 410640 ) - ( 46183 - utoEdp ) ) + ( ( WIVRlPnM / 919105 ) / ( fWhytdDAk + 780496 ) ) ) + ( ( ( hLrD - 83875 ) + ( 408282 / 177212 ) ) + ( ( FL + 41516 ) / ( 83733 + 924443 ) ) ) ) ) ) ) / ( ( ( ( ( ( ( MneloMiJU - lPAYqSPw ) / ( zqSSTAg + 248332 ) ) / ( ( sixv * 470025 ) / ( cmSoez / of ) ) ) / ( ( ( UnklXr - 115228 ) * ( 545385 / saJSyOuS ) ) * ( ( 197120 - lKYd ) + ( rOYMv / 884540 ) ) ) ) * ( ( ( ( kxeKv - VbdFD ) / ( GrUExXLPV - 531812 ) ) + ( ( -5521 * 8494 ) + ( C + OvEEf ) ) ) + ( ( ( 577598 * ouT ) - ( fteJZSP + 636203 ) ) / ( ( 144363 / -10918 ) * ( 246217 - Gs ) ) ) ) ) + ( ( ( ( ( VujnmDnQG + TjRPoj ) + ( 75089 * 165013 ) ) + ( ( bPkFLmR - IiTEXng ) * ( wG * 704779 ) ) ) * ( ( ( e / 977319 ) / ( 136926 + EFwmIe ) ) * ( ( 627767 + S ) - ( 565956 / -49367 ) ) ) ) - ( ( ( ( tXnNEji + -34971 ) + ( 664295 * 29203 ) ) / ( ( 841279 / 851253 ) + ( 632581 + vED ) ) ) - ( ( ( CGIsxIbG - 971812 ) - ( 238159 / 494980 ) ) / ( ( 980100 * OxAQhX ) / ( eDonlpsYc + xNzPw ) ) ) ) ) ) * ( ( ( ( ( ( 116498 - BswdCiJ ) / ( 859103 / I ) ) - ( ( GUCmLzSQe / 650168 ) / ( zgCh * UfMmF ) ) ) * ( ( ( 414719 / J ) + ( rim / 602264 ) ) + ( ( ps * VWEhHLkK ) - ( 728573 * QQKP ) ) ) ) * ( ( ( ( zxp - f ) / ( Scuj * 270993 ) ) + ( ( idVBwaWct + 358993 ) + ( 424751 + Rqiep ) ) ) / ( ( ( Y / 340461 ) * ( 841075 - Yjk ) ) / ( ( SyAZJGQp / 337819 ) * ( sirlRA - 808149 ) ) ) ) ) * ( ( ( ( ( pq / 539963 ) * ( 940505 * 142814 ) ) + ( ( O - -66004 ) * ( AhVhP + LWGtDMQnB ) ) ) - ( ( ( 621587 + 474813 ) * ( lCl / fzywLbA ) ) * ( ( 642507 + 471857 ) * ( 800207 + 768926 ) ) ) ) / ( ( ( ( 262411 / xqnN ) * ( 288184 * uPkY ) ) / ( ( uHGoKIxH + T ) * ( Wg + 48817 ) ) ) - ( ( ( 561296 + bKXJkZIn ) + ( 189547 + -84006 ) ) * ( ( 487109 + 164299 ) * ( rkGEbVISN + ZroWQmgM ) ) ) ) ) ) ) ) ) / ( ( ( ( ( ( ( ( ( 869029 + KMmQxkr ) - ( 827626 * 929216 ) ) - ( ( 905982 / 637407 ) - ( y + x ) ) ) / ( ( ( VTysDefj + 251181 ) / ( 886405 - 91608 ) ) - ( ( CceQVZ - 188984 ) / ( 926135 / 814905 ) ) ) ) - ( ( ( ( 829904 / 100363 ) + ( 939556 * 374169 ) ) / ( ( 203330 * cjXcoNG ) - ( 611326 - 234967 ) ) ) - ( ( ( B + 126818 ) * ( 766788 / JlSBBbgQ ) ) - ( ( 983645 * pZmXAx ) / ( fMXk - 41905 ) ) ) ) ) - ( ( ( ( ( aeYiPbPU - 324941 ) * ( qJFbvZg / 117 ) ) / ( ( 253201 - -85023 ) - ( 931436 + 367506 ) ) ) + ( ( ( 772763 * Uecpth ) / ( lMiTBH - dVDsFKE ) ) + ( ( f - 128117 ) / ( 251735 * 615134 ) ) ) ) - ( ( ( ( 244118 + znq ) - ( 992021 / 425124 ) ) + ( ( 256705 / JBrZTA ) - ( gmjJekBQK / 98210 ) ) ) + ( ( ( KDtyoCBm * kZc ) - ( WYLJD * 173020 ) ) / ( ( 243381 / 434084 ) / ( 883243 - 603806 ) ) ) ) ) ) / ( ( ( ( ( ( X * 725174 ) * ( 637580 * 887261 ) ) * ( ( ulXYAr - pHx ) - ( wNPKRRQQ + qgDrnPSV ) ) ) / ( ( ( eRjpoflt * 444369 ) - ( 321321 / 489944 ) ) + ( ( FhHTIE + 614884 ) / ( 359334 / 64390 ) ) ) ) / ( ( ( ( VrY / 900896 ) - ( nm + 941496 ) ) + ( ( 2687 * GNDtylpLf ) + ( 928153 / 259439 ) ) ) + ( ( ( HB + cttV ) - ( 694892 / 876181 ) ) + ( ( mDqKkaZl / viiMCWS ) - ( dQuV - Z ) ) ) ) ) * ( ( ( ( ( ybLodf - -27776 ) - ( dQ / 993390 ) ) - ( ( -80280 * E ) + ( 262149 / lDgk ) ) ) + ( ( ( -27606 - 206579 ) / ( 797766 * SHDOJ ) ) - ( ( 883056 + 661887 ) + ( 90516 * 615154 ) ) ) ) - ( ( ( ( z * 152009 ) + ( 897368 + s ) ) + ( ( 11727 + 585422 ) - ( 843239 + 120855 ) ) ) + ( ( ( 48651 / b ) / ( z - UOYBc ) ) / ( ( vpAKOTdmp / T ) * ( 167624 * 54494 ) ) ) ) ) ) ) / ( ( ( ( ( ( ( 75579 + tez ) + ( 441795 + 656818 ) ) - ( ( 450150 + -12152 ) * ( moYiJuivO - eL ) ) ) / ( ( ( I + tmgPH ) - ( 824054 + 476750 ) ) + ( ( 359359 * L ) * ( wEnxxlj + rPcW ) ) ) ) / ( ( ( ( auW - MBPyxVZ ) + ( JafPbAjzT - X ) ) / ( ( 92809 / gElwon ) + ( 630924 * 285571 ) ) ) * ( ( ( zFC - R ) * ( 530856 - SJdXi ) ) + ( ( VdL - iX ) - ( -80512 - vQCXIfRCK ) ) ) ) ) * ( ( ( ( ( bgcaElDQ / Audf ) - ( 706053 - mJBs ) ) + ( ( yNXuDMtqU + H ) * ( 508575 / 901454 ) ) ) + ( ( ( 943868 * moLKldJE ) - ( fYIY / 559527 ) ) / ( ( 162374 / k ) / ( 946437 - Ab ) ) ) ) / ( ( ( ( kQnJbt * 988167 ) - ( i + zjnJu ) ) - ( ( 441527 * 888176 ) - ( -37194 + 326434 ) ) ) - ( ( ( 209568 / 316896 ) / ( 268107 * n ) ) + ( ( 279841 + EzeRm ) - ( -24100 * vRQDyeooo ) ) ) ) ) ) + ( ( ( ( ( ( 122939 / -22603 ) * ( 562979 * CQ ) ) - ( ( 829083 / 478273 ) / ( TWn - 658254 ) ) ) / ( ( ( VU * YgB ) - ( 489378 + -14597 ) ) / ( ( 263562 + 428983 ) - ( JGJtbSI * -11866 ) ) ) ) + ( ( ( ( 647570 * 874254 ) + ( CMpRrVAR / AiJJ ) ) / ( ( mvOdkImi + 578993 ) * ( Sgb + CiihUtv ) ) ) - ( ( ( YJUYzPFei * gHDvxYBJG ) + ( 56488 * C ) ) + ( ( C * erLUoW ) / ( nxzNyEg - Yfda ) ) ) ) ) * ( ( ( ( ( E - XOIWIpz ) / ( CznmMTB + zWcgWzh ) ) * ( ( QxtJK / 566001 ) + ( HzZEx * 422805 ) ) ) - ( ( ( 319155 + nkNYfJn ) / ( 640847 * 352198 ) ) * ( ( 858897 + -23555 ) + ( QvMWOIb / 39468 ) ) ) ) - ( ( ( ( 77216 * 510174 ) * ( EHtPP * MMOMJ ) ) / ( ( hGLmj * 273582 ) * ( -44970 / BKsSZk ) ) ) - ( ( ( Uj - eNNE ) + ( 207925 + 296689 ) ) - ( ( YpTre / -74410 ) / ( -44830 * OQv ) ) ) ) ) ) ) ) + ( ( ( ( ( ( ( ( 829961 - 420109 ) + ( jLo * 303370 ) ) + ( ( 287393 / CVmq ) / ( HeunBDer + eWfsHUumU ) ) ) * ( ( ( -38302 * xpccVE ) + ( 334719 * 341188 ) ) - ( ( x * tjTB ) / ( 761922 * -96676 ) ) ) ) + ( ( ( ( gH - EfZ ) * ( fyobMsaZ * hHGr ) ) + ( ( 190061 / 944455 ) / ( 970971 - QJuVtjcqH ) ) ) - ( ( ( 125723 * ifPd ) * ( 228448 * PbLM ) ) - ( ( 707449 + NjOmMaHzu ) + ( 130174 * YAIdhJnU ) ) ) ) ) / ( ( ( ( ( 744918 - LyZ ) * ( pRqxvAi - 941510 ) ) + ( ( ZJBwvSJe + mRozhT ) * ( 660775 * 813098 ) ) ) / ( ( ( 756679 / 907538 ) * ( -56941 * 970500 ) ) + ( ( 896792 + OxLiBkaA ) + ( MsofMYUo + 96345 ) ) ) ) + ( ( ( ( -77477 / -27632 ) / ( FNb - 275319 ) ) + ( ( 56196 + 733891 ) * ( 608608 - F ) ) ) + ( ( ( 833158 - wQnFIDPgv ) / ( 531025 + 819094 ) ) * ( ( 261917 / UJwp ) - ( 558381 * OGSoPr ) ) ) ) ) ) + ( ( ( ( ( ( NwCjLtPf * 1202 ) - ( 344152 - octH ) ) * ( ( 978493 / 835657 ) - ( uEk - 416778 ) ) ) - ( ( ( 760570 + 595751 ) + ( 221959 - 169873 ) ) + ( ( TDeCfw - fkvjUoNI ) + ( aOOQ + 779910 ) ) ) ) * ( ( ( ( 766431 * 820383 ) + ( toYmki * 217854 ) ) - ( ( oDcHL / 73851 ) * ( ruWgXatCv - 515438 ) ) ) + ( ( ( kilvebcTi + ndchmh ) * ( 477412 + ohB ) ) + ( ( r / 223206 ) + ( YhrOBU / 575652 ) ) ) ) ) / ( ( ( ( ( sfFzpXmCY * 797770 ) - ( 881341 * K ) ) * ( ( sqSFqm * 822926 ) - ( pCWhvAMt + 7556 ) ) ) / ( ( ( 537732 * 159864 ) + ( TFoCAgcPa - Kheo ) ) / ( ( RpPaS + 525228 ) / ( 11741 + Xuk ) ) ) ) / ( ( ( ( zDV - x ) * ( G / 66579 ) ) - ( ( tVXhhn * 694881 ) * ( -31349 / 636122 ) ) ) - ( ( ( KQj * AnXw ) / ( 473794 * Fe ) ) + ( ( AwUpNmE / 290270 ) - ( Dhf * 343831 ) ) ) ) ) ) ) * ( ( ( ( ( ( ( -57025 + -91396 ) + ( 380087 / 868560 ) ) * ( ( AG + 540540 ) + ( 507228 - 526248 ) ) ) + ( ( ( RUMwoRby * Eul ) * ( BupokiQpI * 990137 ) ) * ( ( fVH / 607168 ) * ( XUz - tGVNBAqa ) ) ) ) / ( ( ( ( 632217 + 267210 ) + ( 895324 / -92297 ) ) * ( ( -76083 - FJIC ) + ( 221520 + Kp ) ) ) / ( ( ( WnaLFFAUh + SjY ) + ( OxXi - 166767 ) ) + ( ( 318822 + 542831 ) / ( 765308 / nsEtE ) ) ) ) ) - ( ( ( ( ( VnX * OJk ) + ( W + 636978 ) ) * ( ( SyPq * tJDf ) * ( uirc + JOS ) ) ) * ( ( ( 388923 * Q ) * ( 214183 / vs ) ) - ( ( udcsCsS - wypVa ) - ( QYoBW / 649758 ) ) ) ) * ( ( ( ( QJxgryVE / iMrwTy ) / ( JvU - vLBM ) ) / ( ( 852269 - eJJ ) * ( TE + 501960 ) ) ) * ( ( ( sZEm * VuUFGylMq ) * ( 814586 + 764722 ) ) + ( ( y * aAgOz ) + ( vKEHAboL + jPz ) ) ) ) ) ) + ( ( ( ( ( ( 686485 * 637154 ) / ( OtgB * 9801 ) ) * ( ( 610774 / -87497 ) - ( OkOANkURr - 249128 ) ) ) - ( ( ( 897015 + 917365 ) - ( Wuw + BTtUMiP ) ) / ( ( 908175 * -22882 ) * ( 540244 * 268057 ) ) ) ) / ( ( ( ( xzwVndPv + 268569 ) + ( JOYMryW + 376073 ) ) / ( ( 785657 - GSPhEK ) * ( 788373 + -62919 ) ) ) / ( ( ( mKWKBr / 620731 ) / ( 633514 * 941739 ) ) + ( ( lhztGx / CbtPc ) * ( 826009 - AYvPJf ) ) ) ) ) + ( ( ( ( ( 543928 + 300893 ) * ( 40996 - Utbv ) ) + ( ( 523288 / SlskNvscE ) / ( -31793 / 382195 ) ) ) - ( ( ( NSsZfe * 907482 ) * ( tnFCj / 103298 ) ) + ( ( 473990 * 523186 ) + ( 202743 + 113937 ) ) ) ) / ( ( ( ( 767294 - 190991 ) / ( 967882 * rgjr ) ) * ( ( 391138 * 151919 ) - ( 213633 + dQoJAJpe ) ) ) - ( ( ( zVMGi - XHVRTJ ) + ( TKBiIobp + 603655 ) ) / ( ( RrKjw / hwAujEO ) * ( 63754 / 456681 ) ) ) ) ) ) ) ) ) )");
