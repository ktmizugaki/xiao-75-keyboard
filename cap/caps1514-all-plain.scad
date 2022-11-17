include <lib.scad>

for (y = [0:7]) {
  for (x = [0:5]) {
    if (y<=5 || (y<=6&&x<=3)) {
      translate([XOFF_S*x, YOFF*y, ZOFF*0.5]) {
        cap_front(0, "", 0, 1, 1);
        cap_back(0, "", 0, 1, 1);
      }
    } else if (x>=1 && x<=4) {
      translate([-14+XOFF_L*x, YOFF*y, ZOFF*0.5]) {
        cap_front(1, "", 0, 1, 1);
        cap_back(1, "", 0, 1, 1);
      }
    }
  }
}
