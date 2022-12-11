let negated f = (fun x -> not (f x))
let filter_true test op list = List.filter test (List.map op list)
let filter_false test op list = List.filter (negated test) (List.map op list);;

let big_int_list list = 
    List.map Big_int.big_int_of_int list

(* Monkey 0*)
let m1times = ref 1
let m0 = ref (big_int_list [56; 56; 92; 65; 71; 61; 79])
let m0op x = Big_int.mult_big_int x (Big_int.big_int_of_int 8)
let m0test x = Big_int.eq_big_int (Big_int.mod_big_int x (Big_int.big_int_of_int 3)) Big_int.zero_big_int

(* Monkey 1*)
let m1times = ref 0
let m1 = ref (big_int_list [61;85])
let m1op x = Big_int.add_big_int x (Big_int.big_int_of_int 5)
let m1test x =  Big_int.eq_big_int (Big_int.mod_big_int x (Big_int.big_int_of_int 11)) Big_int.zero_big_int

(* Monkey 2*)
let m2times = ref 0
let m2 = ref (big_int_list [54; 96; 82; 78; 69])
let m2op x = Big_int.mult_big_int x x
let m2test x = Big_int.eq_big_int (Big_int.mod_big_int x (Big_int.big_int_of_int 7)) Big_int.zero_big_int

(* Monkey 3*)
let m3times = ref 0
let m3 = ref (big_int_list [57; 59; 65; 95])
let m3op x = Big_int.add_big_int x (Big_int.big_int_of_int 4)
let m3test x = Big_int.eq_big_int (Big_int.mod_big_int x (Big_int.big_int_of_int 2)) Big_int.zero_big_int

(* Monkey 4*)
let m4times = ref 0
let m4 = ref (big_int_list [62; 67; 80])
let m4op x = Big_int.mult_big_int x (Big_int.big_int_of_int 17)
let m4test x = Big_int.eq_big_int (Big_int.mod_big_int x  (Big_int.big_int_of_int 19)) Big_int.zero_big_int;;

(* Monkey 5*)
let m5times = ref 0
let m5 = ref (big_int_list [91])
let m5op x = Big_int.add_big_int x (Big_int.big_int_of_int 7)
let m5test x = Big_int.eq_big_int (Big_int.mod_big_int x (Big_int.big_int_of_int 5)) Big_int.zero_big_int;;

(* Monkey 6*)
let m6times = ref 0
let m6 = ref (big_int_list [79; 83; 64; 52; 77; 56; 63; 92])
let m6op x = Big_int.add_big_int x (Big_int.big_int_of_int 6)
let m6test x = Big_int.eq_big_int (Big_int.mod_big_int x (Big_int.big_int_of_int 17)) Big_int.zero_big_int;;

(* Monkey 7*)
let m7times = ref 0
let m7 = ref (big_int_list [50; 97; 76; 96; 80; 56])
let m7op x = Big_int.add_big_int x (Big_int.big_int_of_int 3)
let m7test x = Big_int.eq_big_int (Big_int.mod_big_int x (Big_int.big_int_of_int 13)) Big_int.zero_big_int;;

for i = 1 to 600 do
        print_string "iteration: ";
        print_int i;
        print_newline ();

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

(*
let print_int_space (x: int) = 
  print_int x;
  print_string " ";
  ()

let print_string_space (x: string) = 
  print_string x;
  print_string " ";
  ()

let print (label:string) list =
  print_newline ();
  print_string label;
  List.iter print_string_space (List.map Big_int.string_of_big_int list);
  print_newline ()
*)

let print_times monkey times = 
  print_string "Monkey";
  print_int monkey;
  print_string " ";
  print_int times;
  print_string " times ";
  print_newline ()
  

(*
let _ = print "m0: " m0.contents
let _ = print "m1: " m1.contents
let _ = print "m2: " m2.contents
let _ = print "m3: " m3.contents
let _ = print "m4: " m4.contents
let _ = print "m5: " m5.contents
let _ = print "m6: " m6.contents
let _ = print "m7: " m7.contents
*)

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

