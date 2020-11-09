type t =
   | Soy
   | Hazelnut
   | Almond
   | Walnut;

let price_of_product = fun
   | Soy => 50
   | Hazelnut => 100
   | Almond => 150
   | Walnut => 200;

let string_of_product = fun
   | Soy => "soy"
   | Hazelnut => "hazelnut"
   | Almond => "almond"
   | Walnut => "walnut";
