open Reprocessing;

type makerState =
   | Bought
   | NotBought;

type t =
   | Maker(makerState)
   | Bottle(Milk.milkState)
   | Product(Product.t);

let draw = (image, env) => fun
   | Maker(makerState) => switch makerState {
      | Bought =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=65 * 2,
            ~height=82 * 2,
            ~texPos=(0, 55),
            ~texWidth=65,
            ~texHeight=82,
            env,
         )
      | NotBought =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=65 * 2,
            ~height=82 * 2,
            ~texPos=(65, 55),
            ~texWidth=65,
            ~texHeight=82,
            env,
         )
   }
   | Bottle(milkState) => switch milkState {
      | Empty =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=23 * 2,
            ~height=52 * 2,
            ~texPos=(130, 55),
            ~texWidth=23,
            ~texHeight=52,
            env,
         )
      | Started =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=23 * 2,
            ~height=52 * 2,
            ~texPos=(130 + 23, 55),
            ~texWidth=23,
            ~texHeight=52,
            env,
         )
      | Half =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=23 * 2,
            ~height=52 * 2,
            ~texPos=(130 + (23 * 2), 55),
            ~texWidth=23,
            ~texHeight=52,
            env,
         )
      | Full =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=23 * 2,
            ~height=52 * 2,
            ~texPos=(130 + (23 * 3), 55),
            ~texWidth=23,
            ~texHeight=52,
            env,
         )
      | OutDated => 
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=23 * 2,
            ~height=52 * 2,
            ~texPos=(130 + (23 * 3), 55),
            ~texWidth=23,
            ~texHeight=52,
            env,
         )
   }
   | Product(product) => switch product {
      | Soy =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=55 * 2,
            ~height=55 * 2,
            ~texPos=(0, 0),
            ~texWidth=55,
            ~texHeight=55,
            env,
         )
      | Hazelnut =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=55 * 2,
            ~height=55 * 2,
            ~texPos=(55, 0),
            ~texWidth=55,
            ~texHeight=55,
            env,
         )
      | Almond =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=55 * 2,
            ~height=55 * 2,
            ~texPos=(55 * 2, 0),
            ~texWidth=55,
            ~texHeight=55,
            env,
         )
      | Walnut =>
         Draw.subImage(
            image,
            ~pos=(0, 0),
            ~width=55 * 2,
            ~height=55 * 2,
            ~texPos=(55 * 3, 0),
            ~texWidth=55,
            ~texHeight=55,
            env,
         )
   }
