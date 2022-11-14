FONT_SYM="DejaVue Sans:style=Bold";
FONT_ARROW="Noto Sans CJK JP:style=Bold";
//FONT="Liberation Sans:style=Bold";
FONT="Nimbus Sans:style=Bold";

SZ_ALP = 3.0;
SZ_NUM = 3.0;
SP_NUM = 1.7;
SZ_SYM = 2.3;
SP_SYM = 1.7;
SZ_FKY = 2.5;
SZ_MOD = 2.5;
SZ_NAV = 2.2;
SZ_LNG = 2.5;


module runner(l) {
    translate([0, 13, 0])
        cube([l,1,1.2], true);
    translate([0, 0.5, 0])
        cube([l,1,1.2], true);
    translate([-3.75, 13, -0.7])
        cube([1.5,1,1.2], true);
    translate([1.75, 13, -0.7])
        cube([1.5,1,1.2], true);
    translate([-3.75, 0.5, -0.7])
        cube([1.5,1,1.2], true);
    translate([1.75, 0.5, -0.7])
        cube([1.5,1,1.2], true);
}

module cap_with_text_and_runner(l, t, p, sz, sp) {
  runner(l!=1? 16: 20);
  is_arrow = t!=""&&((ord(t) >= 9650/*0x25B2*/ && ord(t) <= 9669/*0x25C5*/) || t=="⊕");
  font = is_arrow? FONT_ARROW:
    (sz == SZ_SYM && sp == SP_SYM)? FONT_SYM: FONT;
  yoff =
    (t == "`~") ? 0.0:
    (t == "' \"") ? 0.2:
    (t == "\\ |" || t == "; :") ? 0.5:
    (sz == SZ_SYM && sp == SP_SYM)? 0.5:
    0;

  difference()
  {
    translate([-1, 6.75, -3]) {
      if (l!=1) {
        import("cap1514r-t14-1_00u.stl");
      } else {
        import("cap1514r-t14-1_25u.stl");
      }
    }
    translate([(is_arrow? -0.25: 2.3)+p, 8.8+yoff, -2.1]) {
      rotate([0, 180, 0])
        linear_extrude(height = 1)
        if (t == "debian") {
          translate([p+1, -3.2-yoff, 0]) scale(0.16) import("debian-openlogo-nd-simplified.svg");
        } else if (t == "hexagon") {
          translate([p+1.6, -0.3-yoff, 0]) scale(0.2) import("hexagon.svg");
        } else if (t == "backspace") {
          translate([p-0.5, -2.4-yoff, 0]) scale(0.45) import("backspace.svg");
        } else {
          text(t, size=sz, spacing=sp, font=font, halign = "left", valign = "baseline", $fn=30);
        }
    }
  }
}

module cap_front(l, t, p, sz, sp) {
  rotate([-90, 180, 0])
    cap_with_text_and_runner(l, t, p, sz, sp);
}

module cap_back(l, t, p, sz, sp) {
  rotate([90, 0, 0])
    cap_with_text_and_runner(l, t, p, sz, sp);
}

module cap_pair(l, t1, p1, t2, p2, sz, sp) {
  cap_front(l, t1, p1, sz, sp);
  cap_back(l, t2, p2, sz, sp);
}

module cap_rendered(id) {
  import(str("caps/cap1514r-t14-sup-", (id < 10? "0": ""), id, ".stl"));
}

module cap_array(start, end, npl) {
  for (id = [start:end]) {
    xoff = id <= 40? XOFF_S: XOFF_L;
    x = (id-start)%npl;
    y = floor((id-start)/npl);
    if (x == 0) {
      translate([-(xoff-0.5)/2, YOFF*y, ZOFF*0.5])
        cube([1.0,1.2,13.5], true);
    }
    if (x == npl-1 || id==end) {
      translate([xoff*x+(xoff-0.5)/2, YOFF*y, ZOFF*0.5])
        cube([1.0,1.2,13.5], true);
    }
    translate([xoff*x, YOFF*y, 0]) cap_rendered(id);
  }
}

XOFF_S = 15.5;
XOFF_L = XOFF_S + 4;
YOFF = 11;
ZOFF = 13.5;
