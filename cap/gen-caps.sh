#!/bin/bash
KEYS=(
    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    '1!' '2@' '3#' '4$' '5%' '6^' '7&' '8*' '9(' '0)'
    '[ {' '] }' ', <' '. >' '; :' "' \"" '\\ |' '/ ?' '- _' '=+' '`~' 'debian'
    F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12 Fn Fn
    Esc Del Alt Alt Win Win EI Ctrl
    PgUp PgDn Home End '▲' '▼' '◀' '▶' 'hexagon' 'hexagon'
)
LKEYS=(
    Shift Shfit CapsL Ctrl Tab Ctrl Enter 'backspace' ' ' ' '
)

unset t1 t2
p=0
sz=3.8
sp=1
id=0

function gen_key() {
    (( id ++ ))
    if [ $id == 1 ]; then
      # alphabets
      p=0
      sz=3.0
      sp=1
    elif [ $id == 14 ]; then
      # numbers
      p=0.4
      sz=3.0
      sp=1.7
    elif [ $id == 19 ]; then
      # symbols
      p=0
      sz=2.3
      sp=1.7
    elif [ $id == 25 ]; then
      # F-keys
      p=0.4
      sz=2.5
      sp=1
    elif [ $id == 32 ]; then
      # modifiers
      p=0.4
      sz=2.5
      sp=1
    elif [ $id == 36 ]; then
      # navigations
      p=0.8
      sz=2.2
      sp=1
    elif [ $id == 41 ]; then
      # long keys
      l=1
      p=2
      sz=2.5
      sp=1
    fi
    n=$(printf %02d "$id")
    f="caps/cap1514r-t14-sup-$n.stl"
    t1=${t1//\"/\\\"}
    t2=${t2//\"/\\\"}
    if ! [ -e "$f" ]; then
        echo "gen $id: $t1 $t2 ($p, $sz, $sp)"
        cat >tmp.scad <<EOF
include <lib.scad>
cap_pair($l, "$t1", $p, "$t2", $p, $sz, $sp);
EOF
        openscad -o "$f" tmp.scad
        rm tmp.scad
    fi
    unset t1 t2
}

l=0
for key in "${KEYS[@]}"; do
    if [ -z "${t1+isset}" ]; then
        t1="$key"
    else
        t2="$key"
        gen_key
    fi
done

if [ "$t1" ]; then
    gen_key
fi

l=1
for key in "${LKEYS[@]}"; do
    if [ -z "${t1+isset}" ]; then
        t1="$key"
    else
        t2="$key"
        gen_key
    fi
done
if [ "$t1" ]; then
    gen_key
fi

for f in caps1514-all.stl caps1514-all-plain.stl; do
  if ! [ -e "$f" ]; then
    echo "gen $f"
    openscad --export-format binstl -o $f ${f/stl/scad}
  fi
done
