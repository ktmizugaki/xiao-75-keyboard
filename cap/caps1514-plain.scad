for (z = [0:1]) {
  for (y = [0:7]) {
    for (x = [0:5]) {
      if (z<=0 || y<=3 || (y<=5&&x<=3)) {
        translate([15.5*x, 8*y, 18.5*z])
          rotate([-90, 180, 0])
            translate([-1, 6.75, -3])
                import("cap1514r-t14-1_00u.stl");
      } else if (x>=1 && x<=4) {
        translate([-14+19.5*x, 8*y, 18.5*z])
          rotate([-90, 180, 0])
            translate([-1, 6.75, -3])
                import("cap1514r-t14-1_25u.stl");
      }
    }
  }
}
