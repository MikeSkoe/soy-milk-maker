
open Reprocessing;

let draw = (env, _state) => {
    Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
    Draw.fill(Constants.black, env);
    Draw.text(~body="menu", ~pos=(10, 10), env);
};
