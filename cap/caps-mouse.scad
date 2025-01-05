USE_RUNNER = 1;

module runner() {
  translate([-1, -1, -0.6]) cube([2, 2, 1.2]);
  translate([0, 1-sqrt(3), -0.6]) rotate([0, 0, -30]) cube([1.4, 2, 1.2]);
}

module caps_mouse() {
  translate([0, 0, 0.0]) import("cap-JT8P.stl");
  translate([-13.3,  0, 1.2]) rotate([0, 0, 90]) import("cap-xswitch.stl");
  translate([13.3, 0, 1.2]) rotate([0, 0, -90]) import("cap-xswitch.stl");

  if (USE_RUNNER) translate([0,0,1.3]) {
    translate([-6.3, 3.2, 0]) rotate([0, 0, 0]) runner();
    translate([-6.3, -3.2, 0]) rotate([180, 0, 0]) runner();
    translate([6.3, 3.2, 0]) rotate([0, 180, 0]) runner();
    translate([6.3, -3.2, 0]) rotate([0, 0, 180]) runner();
  }
}

caps_mouse();
