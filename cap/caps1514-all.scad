include <lib.scad>

cap_array(1, 40, 6);
translate([XOFF_S*4+2, YOFF*6, 0])
  cap_array(41, 41, 6);
translate([2, YOFF*7, 0])
  cap_array(42, 45, 5);
