type t =
   | Soy
   | Nut
   | Coconut;

let price_of_product = fun
   | Soy => 50
   | Nut => 100
   | Coconut => 150;

let string_of_product = fun
   | Soy => "soy"
   | Nut => "nut"
   | Coconut => "coconut";
