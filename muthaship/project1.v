`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 09/13/2023 06:51:50 PM
// Design Name:
// Module Name: project1
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


module project1(
    A,
    B,
    C,
    D
    );
   
    input wire [0:0]A;
    input wire [0:0]B;
    input wire [0:0]C;
    output wire [0:0]D;
   
   
    wire wire1;
   
   
   
    or(wire1, A,B);
    and(D,C,wire1);
   
   
endmodule