/**
* Gimbal test stand for model rockets.
*
* Units: mm
*
* CGrassin, 2020, MIT License
**/

// --- Settings ---
// Inside diameter of the rocket's body (in mm).
rocket_diameter = 70;

// --- Code ---
rocket_test_stand(rocket_diameter);

module rocket_test_stand(rocket_diameter,stand_height=55,base_screw_holes=true) {
    // Internal variables
    stand_width = 3;
    stand_base_height = 2;
    stand_base_diameter = stand_width + 15;
    stand_taper_base = 2;
    screw_holes_dia = 3.2;
    
    difference(){
        // Main body (tube)
        union(){
            // Main truncated cone shape
            cylinder(stand_height, d1=rocket_diameter+stand_width+stand_taper_base*2,d2=rocket_diameter+stand_width,$fn=200);
            
            // Base ring
            cylinder(stand_base_height, d=rocket_diameter+stand_base_diameter,$fn=200);
            
            // Chamfer
            translate([0,0,stand_base_height]) cylinder(stand_base_height+10, d1=rocket_diameter+stand_base_diameter,d2=rocket_diameter,$fn=200);
        }
        // Inside
        cylinder(stand_height+1, d=rocket_diameter,$fn=100);
        
        // Gimbal screw holes
        for(i = [0:90:360])
        rotate([0,0,i]) translate([0, 0, stand_height-1.5*screw_holes_dia]) rotate([0, 90, 0]) cylinder(rocket_diameter, d=screw_holes_dia,$fn=20);
        
        // Remove side material
        cut = rocket_diameter/3.2;
        for(i = [45:90:360]) translate([0,0,stand_base_height]) rotate([0, -90, i]) linear_extrude(rocket_diameter) polygon([[0,-cut],[0,cut],[stand_height,cut],[stand_height,-cut]]);
        
        // Base screw holes
        if(base_screw_holes) {
            for(i = [45:90:360]) rotate([0,0,i]) translate([(rocket_diameter+stand_base_diameter/2)/2,0,0]) cylinder(stand_base_height,d=screw_holes_dia,$fn=20);
        }
    }
}
