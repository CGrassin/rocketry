/**
* PCB holder for model rockets.
* Use with "Sagan" PCB.
*
* Units: mm
*
* CGrassin, 2020, MIT License
**/

// --- Settings ---
// Inside diameter of the rocket's body (in mm).
rocket_diameter = 70;

// --- Code ---
rocket_PCB_holder(rocket_diameter);


module rocket_PCB_holder(rocket_diameter) {
    // --- Internal variables ---
    //PCB
    PCB_holes_diameter = 3.2;
    PCB_holes_spacing = 32.51;
    //Ring
    ring_width = 1.5;
    ring_heigth = 6;
    //Screw blocks
    screw_block_nb = 2;
    screw_block_width = 5;
    screw_block_taper = 2.5;
    screw_block_length = 6;
    screw_block_diameter = 3;

    // --- Computed variables ---
    a = sqrt(pow(rocket_diameter/2,2)-pow((screw_block_width+2*screw_block_taper)/2,2))-screw_block_length/2;

    // Ring
    difference() {
        union(){
            // Main tube
            difference() {
                cylinder(ring_heigth,d=rocket_diameter,center=true,$fn=200);
                cylinder(ring_heigth+1,d=rocket_diameter-ring_width*2,center=true,$fn=200);
            }
            
            // Screw blocks
           for(i = [0:360/screw_block_nb:360]) rotate([0, 0, i]) 
               translate([0,a,0]) 
               linear_extrude(ring_heigth,center=true)
               translate([-screw_block_width/2,-screw_block_length/2,0]) 
               polygon(points=[[0,0],[-screw_block_taper,screw_block_length],[screw_block_width+screw_block_taper,screw_block_length],[screw_block_width,0]]);
        }
        
        // Screw blocks hole
        for(i = [0:360/screw_block_nb:360]) rotate([0, 0, i]) translate([0,a,0]) rotate([90, 0, 0]) cylinder(screw_block_length+3, d=screw_block_diameter, $fn=20, center=true);
    }

    // Central bar
    difference() {
        cube([rocket_diameter, ring_width, ring_heigth],center=true);
        
        for(i = [-PCB_holes_spacing/2,PCB_holes_spacing/2])
            translate([i,0,0]) rotate([90, 0, 0]) cylinder(ring_width+1,d=PCB_holes_diameter,$fn=100,center=true);
    }
}