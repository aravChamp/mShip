`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 09/13/2023 06:56:40 PM
// Design Name:
// Module Name: sim1
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////


module sim1;
    reg [2:0]swt;
    wire D;
    integer i;
    reg e_output;
   
    project1 ttul(.A(swt[2]),.B(swt[1]),.C(swt[0]),.D(D));
   
    function expected_led;
        input [2:0] switch;
        begin
            expected_led = switch[2] | switch[1] & switch[0];
        end
    endfunction
   
initial
begin
    for(i=0; i<8; i=i+1)
    begin
        #50 swt = i;
        #10 e_output = expected_led(swt);
        // the disp
        if (D == e_output)
            $display("LED output matched at %t\n", $time);
        else
            $display("LED output mis-mstched at %t, expected %b, actual %b\n, $time, e_output, D");
    end
end
endmodule