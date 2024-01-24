include <lib.scad>

// "Win" "hexagon" "debian"
WINKEY="Win";

translate([0, 0, 14*5]) {
  translate([15* 0, 0, 0]) cap_front(0, "Esc", 0.4, SZ_MOD, 1);
  translate([2, 0, 0]) {
  translate([15* 1, 0, 0]) cap_front(0, "F1", 0.4, SZ_FKY, 1);
  translate([15* 2, 0, 0]) cap_front(0, "F2", 0.4, SZ_FKY, 1);
  translate([15* 3, 0, 0]) cap_front(0, "F3", 0.4, SZ_FKY, 1);
  translate([15* 4, 0, 0]) cap_front(0, "F4", 0.4, SZ_FKY, 1);
  }
  translate([4, 0, 0]) {
  translate([15* 5, 0, 0]) cap_front(0, "F5", 0.4, SZ_FKY, 1);
  translate([15* 6, 0, 0]) cap_front(0, "F6", 0.4, SZ_FKY, 1);
  translate([15* 7, 0, 0]) cap_front(0, "F7", 0.4, SZ_FKY, 1);
  translate([15* 8, 0, 0]) cap_front(0, "F8", 0.4, SZ_FKY, 1);
  }
  translate([6, 0, 0]) {
  translate([15* 9, 0, 0]) cap_front(0, "F9", 0.4, SZ_FKY, 1);
  translate([15*10, 0, 0]) cap_front(0, "F10", 0.4, SZ_FKY, 1);
  translate([15*11, 0, 0]) cap_front(0, "F11", 0.4, SZ_FKY, 1);
  translate([15*12, 0, 0]) cap_front(0, "F12", 0.4, SZ_FKY, 1);
  }
  translate([8, 0, 0]) {
  translate([15*13, 0, 0]) cap_front(0, "Del", 0.4, SZ_MOD, 1);
  }
}
translate([0, 0, 14*4]) {
  translate([15* 0, 0, 0]) cap_front(0, "`~", 0, SZ_SYM, SP_SYM);
  translate([15* 1, 0, 0]) cap_front(0, "1!", 0.4, SZ_NUM, SP_NUM);
  translate([15* 2, 0, 0]) cap_front(0, "2@", 0.4, SZ_NUM, SP_NUM);
  translate([15* 3, 0, 0]) cap_front(0, "3#", 0.4, SZ_NUM, SP_NUM);
  translate([15* 4, 0, 0]) cap_front(0, "4$", 0.4, SZ_NUM, SP_NUM);
  translate([15* 5, 0, 0]) cap_front(0, "5%", 0.4, SZ_NUM, SP_NUM);
  translate([15* 6, 0, 0]) cap_front(0, "6^", 0.4, SZ_NUM, SP_NUM);
  translate([15* 7, 0, 0]) cap_front(0, "7&", 0.4, SZ_NUM, SP_NUM);
  translate([15* 8, 0, 0]) cap_front(0, "8*", 0.4, SZ_NUM, SP_NUM);
  translate([15* 9, 0, 0]) cap_front(0, "9(", 0.4, SZ_NUM, SP_NUM);
  translate([15*10, 0, 0]) cap_front(0, "0)", 0.4, SZ_NUM, SP_NUM);
  translate([15*11, 0, 0]) cap_front(0, "- _", 0, SZ_SYM, SP_SYM);
  translate([15*12, 0, 0]) cap_front(0, "=+", 0, SZ_SYM, SP_SYM);
  translate([2, 0, 0]) {
  translate([15*13, 0, 0]) cap_front(1, "backspace", 2, SZ_LNG, 1);
  }
}
translate([4, 0, 14*3]) {
  translate([-2+15*0, 0, 0]) cap_front(1, "Tab", 2, SZ_LNG, 1);
  translate([15* 1, 0, 0]) cap_front(0, "Q", 0, SZ_ALP, 1);
  translate([15* 2, 0, 0]) cap_front(0, "W", 0, SZ_ALP, 1);
  translate([15* 3, 0, 0]) cap_front(0, "E", 0, SZ_ALP, 1);
  translate([15* 4, 0, 0]) cap_front(0, "R", 0, SZ_ALP, 1);
  translate([15* 5, 0, 0]) cap_front(0, "T", 0, SZ_ALP, 1);
  translate([15* 6, 0, 0]) cap_front(0, "Y", 0, SZ_ALP, 1);
  translate([15* 7, 0, 0]) cap_front(0, "U", 0, SZ_ALP, 1);
  translate([15* 8, 0, 0]) cap_front(0, "I", 0, SZ_ALP, 1);
  translate([15* 9, 0, 0]) cap_front(0, "O", 0, SZ_ALP, 1);
  translate([15*10, 0, 0]) cap_front(0, "P", 0, SZ_ALP, 1);
  translate([15*11, 0, 0]) cap_front(0, "[ {", 0, SZ_SYM, SP_SYM);
  translate([15*12, 0, 0]) cap_front(0, "] }", 0, SZ_SYM, SP_SYM);
  translate([15*13, 0, 0]) cap_front(0, "\\ |", 0, SZ_SYM, SP_SYM);
}
translate([8, 0, 14*2]) {
  translate([-2+15*0, 0, 0]) cap_front(1, "CapsL", 2, SZ_LNG, 1);
  translate([15* 1, 0, 0]) cap_front(0, "A", 0, SZ_ALP, 1);
  translate([15* 2, 0, 0]) cap_front(0, "S", 0, SZ_ALP, 1);
  translate([15* 3, 0, 0]) cap_front(0, "D", 0, SZ_ALP, 1);
  translate([15* 4, 0, 0]) cap_front(0, "F", 0, SZ_ALP, 1);
  translate([15* 5, 0, 0]) cap_front(0, "G", 0, SZ_ALP, 1);
  translate([15* 6, 0, 0]) cap_front(0, "H", 0, SZ_ALP, 1);
  translate([15* 7, 0, 0]) cap_front(0, "J", 0, SZ_ALP, 1);
  translate([15* 8, 0, 0]) cap_front(0, "K", 0, SZ_ALP, 1);
  translate([15* 9, 0, 0]) cap_front(0, "L", 0, SZ_ALP, 1);
  translate([15*10, 0, 0]) cap_front(0, "; :", 0, SZ_SYM, SP_SYM);
  translate([15*11, 0, 0]) cap_front(0, "' \"", 0, SZ_SYM, SP_SYM);
  translate([2+15*12, 0, 0]) cap_front(1, "Enter", 2, SZ_LNG, 1);
}
translate([16, 0, 14*1]) {
  translate([-10+15*0, 0, 0]) cap_front(1, "Shift", 2, SZ_LNG, 1);
  translate([15* 1, 0, 0]) cap_front(0, "Z", 0, SZ_ALP, 1);
  translate([15* 2, 0, 0]) cap_front(0, "X", 0, SZ_ALP, 1);
  translate([15* 3, 0, 0]) cap_front(0, "C", 0, SZ_ALP, 1);
  translate([15* 4, 0, 0]) cap_front(0, "V", 0, SZ_ALP, 1);
  translate([15* 5, 0, 0]) cap_front(0, "B", 0, SZ_ALP, 1);
  translate([15* 6, 0, 0]) cap_front(0, "N", 0, SZ_ALP, 1);
  translate([15* 7, 0, 0]) cap_front(0, "M", 0, SZ_ALP, 1);
  translate([15* 8, 0, 0]) cap_front(0, ", <", 0, SZ_SYM, SP_SYM);
  translate([15* 9, 0, 0]) cap_front(0, ". >", 0, SZ_SYM, SP_SYM);
  translate([15*10, 0, 0]) cap_front(0, "/ ?", 0, SZ_SYM, SP_SYM);
  translate([2+15*11, 0, 0]) cap_front(1, "Shift", 2, SZ_LNG, 1);
}
translate([12, 0, 14*0]) {
  translate([-2+15*0, 0, 0]) cap_front(1, "Ctrl", 2, SZ_LNG, 1);
  translate([15* 1, 0, 0]) cap_front(0, "Fn", 0.4, SZ_FKY, 1);
  translate([15* 2, 0, 0]) cap_front(0, WINKEY, 0.4, SZ_MOD, 1);
  translate([15* 3, 0, 0]) cap_front(0, "Alt", 0.4, SZ_MOD, 1);
  translate([2+15* 4, 0, 0]) cap_front(1, "", 2, SZ_LNG, 1);
  translate([6+15* 5, 0, 0]) cap_front(1, "", 2, SZ_LNG, 1);
  translate([8, 0, 0]) {
  translate([15* 6, 0, 0]) cap_front(0, "Alt", 0.4, SZ_MOD, 1);
  translate([15* 7, 0, 0]) cap_front(0, WINKEY, 0.4, SZ_MOD, 1);
  translate([15* 8, 0, 0]) cap_front(0, "EI", 0.4, SZ_MOD, 1);
  translate([15* 9, 0, 0]) cap_front(0, "Fn", 0.4, SZ_FKY, 1);
  translate([15*10, 0, 0]) cap_front(0, "Ctrl", 0.4, SZ_MOD, 1);
  }
}

translate([8+15*14, 0, 0]) {
  translate([-15*2, 0, 0]) cap_front(0, "◀", 0.8, SZ_NAV, 1);
  translate([-15*1, 0, 0]) cap_front(0, "▼", 0.8, SZ_NAV, 1);
  translate([-15*1, 0, 14]) cap_front(0, "▲", 0.8, SZ_NAV, 1);
  translate([-15*0, 0, 0]) cap_front(0, "▶", 0.8, SZ_NAV, 1);
  translate([0, 0, 14*4]) cap_front(0, "Home", 0.8, SZ_NAV, 1);
  translate([0, 0, 14*3]) cap_front(0, "PgUp", 0.8, SZ_NAV, 1);
  translate([0, 0, 14*2]) cap_front(0, "PgDn", 0.8, SZ_NAV, 1);
  translate([0, 0, 14*1]) cap_front(0, "End", 0.8, SZ_NAV, 1);
}
