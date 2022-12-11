let negated f = (fun x -> not (f x))
let filter_true test op list = List.filter test (List.map op list)
let filter_false test op list = List.filter (negated test) (List.map op list);;

(* Monkey 0*)
let m0times = ref 1
let m0 = ref [56; 56; 92; 65; 71; 62; 79]
let m0op x = Float.to_int(Int.to_float(x * 7) /. 3.)
let m0test x = (x mod 3) = 0

(* Monkey 1*)
let m1times = ref 0
let m1 = ref [61;85]
let m1op x = Float.to_int(Int.to_float(x + 5) /. 3.)
let m1test x = (x mod 11) = 0

(* Monkey 2*)
let m2times = ref 0
let m2 = ref [54; 96; 82; 78; 69]
let m2op x = Float.to_int(Int.to_float(x * x) /. 3.)
let m2test x = (x mod 7) = 0

(* Monkey 3*)
let m3times = ref 0
let m3 = ref [57; 59; 65; 95]
let m3op x = Float.to_int(Int.to_float(x + 4) /. 3.)
let m3test x = (x mod 2) = 0;;

(* Monkey 4*)
let m4times = ref 0
let m4 = ref [62; 67; 80]
let m4op x = Float.to_int(Int.to_float(x*17) /. 3.)
let m4test x = (x mod 19) = 0;;

(* Monkey 5*)
let m5times = ref 0
let m5 = ref [91]
let m5op x = Float.to_int(Int.to_float(x+7) /. 3.)
let m5test x = (x mod 5) = 0;;

(* Monkey 6*)
let m6times = ref 0
let m6 = ref [79; 83; 64; 52; 77; 56; 63; 92]
let m6op x = Float.to_int(Int.to_float(x+6) /. 3.)
let m6test x = (x mod 17) = 0;;

(* Monkey 7*)
let m7times = ref 0
let m7 = ref [50; 97; 76; 96; 80; 56]
let m7op x = Float.to_int(Int.to_float(x+3) /. 3.)
let m7test x = (x mod 13) = 0;;

for _ = 1 to 20 do
  (* Round *)
  m0times := m0times.contents + List.length m0.contents;
  m3 := List.append m3.contents (filter_true m0test m0op m0.contents);
  m7 := List.append m7.contents (filter_false m0test m0op m0.contents);
  m0 := [];

  m1times := m1times.contents + List.length m1.contents;
  m6 := List.append m6.contents (filter_true m1test m1op m1.contents);
  m4 := List.append m4.contents (filter_false m1test m1op m1.contents);
  m1 := [];

  m2times := m2times.contents + List.length m2.contents;
  m0 := List.append m0.contents (filter_true m2test m2op m2.contents);
  m7 := List.append m7.contents (filter_false m2test m2op m2.contents);
  m2 := [];

  m3times := m3times.contents + List.length m3.contents;
  m5 := List.append m5.contents (filter_true m3test m3op m3.contents);
  m1 := List.append m1.contents (filter_false m3test m3op m3.contents);
  m3 := [];

  m4times := m4times.contents + List.length m4.contents;
  m2 := List.append m2.contents (filter_true m4test m4op m4.contents);
  m6 := List.append m6.contents (filter_false m4test m4op m4.contents);
  m4 := [];

  m5times := m5times.contents + List.length m5.contents;
  m1 := List.append m1.contents (filter_true m5test m5op m5.contents);
  m4 := List.append m4.contents (filter_false m5test m5op m5.contents);
  m5 := [];

  m6times := m6times.contents + List.length m6.contents;
  m2 := List.append m2.contents (filter_true m6test m6op m6.contents);
  m0 := List.append m0.contents (filter_false m6test m6op m6.contents);
  m6 := [];

  m7times := m7times.contents + List.length m7.contents;
  m3 := List.append m3.contents (filter_true m7test m7op m7.contents);
  m5 := List.append m5.contents (filter_false m7test m7op m7.contents);
  m7 := [];
done;;

let print_int_space (x: int) = 
  print_int x;
  print_string " ";
  ()

let print (label:string) list =
  print_newline ();
  print_string label;
  List.iter print_int_space list;
  print_newline ()

let print_times monkey times = 
  print_string "Monkey";
  print_int monkey;
  print_string " ";
  print_int times;
  print_string " times ";
  print_newline ()
  

let _ = print "m0: " m0.contents
let _ = print "m1: " m1.contents
let _ = print "m2: " m2.contents
let _ = print "m3: " m3.contents
let _ = print "m4: " m4.contents
let _ = print "m5: " m5.contents
let _ = print "m6: " m6.contents
let _ = print "m7: " m7.contents

let _ = print_newline ()

let _ = print_times 0 m0times.contents
let _ = print_times 1 m1times.contents
let _ = print_times 2 m2times.contents
let _ = print_times 3 m3times.contents
let _ = print_times 4 m4times.contents
let _ = print_times 5 m5times.contents
let _ = print_times 6 m6times.contents
let _ = print_times 7 m7times.contents

let times = List.rev
    (List.sort compare
      [m0times.contents; m1times.contents; m2times.contents; m3times.contents;
       m4times.contents; m5times.contents; m6times.contents; m7times.contents])

let score = (List.nth times 0) * (List.nth times 1)

let _ =
  print_string "Score = ";
  print_int score;
  print_newline ()
