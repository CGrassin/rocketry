/**
* PCB holder for model rockets.
* Use with "Sagan" PCB.
*
* CGrassin, 2020, MIT License
**/

// TODO change screw blocks from cube to trapeze shape
// TODO add filet to screw blocks

// --- Settings ---
// Inside diameter of the rocket's body (in mm).
rocket_diameter = 70;

// --- Internal variables ---
PCB_holes_diameter = 3.2;
PCB_holes_spacing = 32.51;
ring_width = 2;
ring_heigth = 6;
screw_block_nb = 2;
screw_block_width = 6;
screw_block_diameter = 3;

// --- Code ---
a = sqrt(pow(rocket_diameter/2,2)-pow(screw_block_width/2,2))-screw_block_width/2;

// Ring
difference() {
    //
    union(){
        // Main tube
        difference() {
            cylinder(ring_heigth,d=rocket_diameter,center=true,$fn=200);
            cylinder(ring_heigth+1,d=rocket_diameter-ring_width*2,center=true,$fn=200);
        }
        
        // Screw blocks
        for(i = [0:360/screw_block_nb:360]) rotate([0, 0, i]) translate([0,a,0]) cube([screw_block_width,screw_block_width,ring_heigth],center=true);
    }
    
    // Screw blocks hole
    for(i = [0:360/screw_block_nb:360]) rotate([0, 0, i]) translate([0,rocket_diameter/2-ring_heigth/2,0]) rotate([90, 0, 0]) cylinder(10+1, d=screw_block_diameter, $fn=20, center=true);
}

// Central bar
difference() {
    cube([rocket_diameter, ring_width, ring_heigth],center=true);
    
    for(i = [-PCB_holes_spacing/2,PCB_holes_spacing/2])
        translate([i,0,0]) rotate([90, 0, 0]) cylinder(ring_width+1,d=PCB_holes_diameter,$fn=100,center=true);
}