// THERE MUST BE NO MORE THAN 256 VERTICES
// scale= 47.36865
#define NTRIANGLES 256
#define NVERTICES  150
PROGMEM const int16_t vertices[NVERTICES*3]={
49,36,0,43,38,30,53,36,0,22,36,48,23,36,51,-6,36,56,-6,36,59,-35,37,48,-56,37,29,-64,37,0,-56,38,-29,
-34,36,-47,-36,36,-50,-6,36,-55,-6,36,-58,23,38,-49,42,36,-27,45,36,-29,54,13,36,63,13,0,60,-7,39,71,
-7,0,63,-26,41,74,-26,0,29,13,61,33,-7,67,34,-26,70,-6,13,70,-6,-7,77,-6,-26,80,-40,21,58,-45,-7,67,-47,
-26,70,-66,13,36,-73,-7,39,-75,-26,41,-76,13,0,-83,-7,0,-66,13,-35,-73,-7,-38,-75,-26,-40,-41,13,-60,
-45,-7,-66,-47,-26,-69,-6,13,-69,-6,-7,-76,-6,-26,-79,29,13,-60,33,-7,-66,34,-26,-69,54,13,-35,60,-7,
-38,63,-26,-40,58,-41,38,69,-41,0,43,-59,29,51,-59,0,32,-41,65,23,-59,50,-6,-41,75,-6,-59,57,-44,-41,
65,-35,-59,50,-71,-41,38,-81,-41,0,-63,-59,0,-71,-41,-37,-55,-59,-28,-44,-41,-64,-6,-41,-74,-6,-59,-56,
32,-41,-64,23,-59,-49,58,-41,-37,34,-61,16,-6,-62,0,-22,-61,41,-55,-59,29,-47,-61,-15,-35,-59,-49,9,-61,
-40,43,-59,-28,-69,21,8,-116,19,9,-113,14,0,-98,25,8,-121,8,9,-66,27,4,-67,25,-7,-98,27,-2,-119,22,-2,
-126,10,-2,-71,19,-2,-108,19,-7,-116,-7,9,-102,-22,9,-107,-9,1,-86,-26,0,-82,-37,4,-107,-23,0,-122,-6,
-2,-118,5,-7,-106,-19,-8,-84,-33,-8,62,-5,0,62,-13,18,87,-3,15,85,2,0,100,23,8,97,26,0,62,-29,18,93,-13,
15,102,12,10,122,36,6,62,-38,0,95,-18,0,106,10,0,62,-29,-17,93,-13,-14,102,12,-9,62,-13,-17,87,-3,-14,
127,35,0,118,33,-7,3,63,6,-13,60,14,-6,46,8,-20,60,-7,1,60,-13,-5,46,-7,11,42,10,21,38,33,39,34,27,42,
36,0,20,34,45,-18,42,17,-4,36,49,-39,38,28,-32,34,45,-51,34,27,-23,42,-11,-54,36,1,-34,38,-32,-51,34,
-26,-32,34,-44,-7,36,-48,4,42,-17,27,38,-27,20,34,-44,39,34,-26,
};
PROGMEM const int16_t normals[NVERTICES*3]={
11,126,-3,67,96,47,72,104,3,2,126,11,34,95,76,1,126,8,-5,106,69,-40,96,72,-98,57,57,-114,53,-10,-78,80,
-58,-2,126,-12,-34,95,-76,-3,126,-11,3,104,-72,47,96,-67,12,126,-2,76,95,-34,101,49,58,117,48,0,106,31,
61,122,31,0,109,-11,62,126,-11,0,58,48,101,61,31,106,63,-11,109,0,48,117,0,31,122,0,-11,126,-61,53,97,
-61,32,106,-62,-11,109,-104,48,53,-106,32,61,-109,-11,63,-117,48,0,-122,31,0,-101,49,-58,-106,31,-61,
-109,-11,-62,-58,48,-101,-61,31,-106,-63,-11,-109,0,48,-117,0,31,-122,0,-11,-126,58,49,-101,61,31,-106,
62,-11,-109,101,48,-58,106,31,-61,109,-11,-63,93,-67,52,107,-67,-1,58,-109,27,64,-109,-4,60,-62,92,30,
-111,52,4,-70,105,0,-113,56,-52,-67,93,-27,-109,58,-92,-67,54,-107,-67,1,-64,-109,4,-93,-67,-52,-58,-109,
-27,-54,-67,-92,-1,-67,-107,-4,-109,-64,52,-67,-93,27,-109,-58,92,-67,-54,9,-126,3,0,-127,0,-3,-126,9,
-45,-114,30,-9,-126,-3,-30,-114,-45,3,-126,-9,45,-114,-30,6,-24,124,-34,-10,121,108,-52,38,-12,101,75,
-53,-11,114,2,119,44,2,64,-109,-13,121,-33,-62,99,-47,-123,23,-20,12,-124,-18,13,-18,-124,-10,-21,124,
22,9,124,105,70,8,-111,59,11,-34,-99,71,-80,-98,1,-112,-53,-25,18,6,-125,7,9,-126,-40,-76,-93,-40,119,
17,-6,44,118,-24,65,105,-82,96,0,-56,45,104,-102,66,-33,49,-78,86,68,-31,102,65,-22,106,47,-23,115,62,
-108,-17,98,-80,0,111,-59,-8,31,-37,-117,66,-53,-94,95,-40,-73,-24,86,-89,-12,36,-120,97,-78,19,67,-41,
-99,109,44,47,-51,28,112,-23,89,87,-113,27,-49,59,26,-108,50,89,-74,20,124,15,27,120,28,43,114,32,30,
123,0,33,112,47,-12,124,21,0,123,30,-28,120,27,-32,114,43,-47,112,33,-19,124,-14,-30,123,0,-27,120,-28,
-43,114,-32,-33,112,-47,0,123,-30,12,124,-21,28,120,-27,32,114,-43,47,112,-33,
};

PROGMEM const uint16_t triangles[NTRIANGLES*3]={
0,1,2,1,3,4,3,5,6,3,6,4,5,7,6,6,7,30,7,8,30,10,11,12,11,13,14,11,14,12,13,15,14,15,16,17,16,0,2,16,2,
17,2,1,18,2,18,19,19,18,20,19,20,21,21,20,22,21,22,23,1,4,24,1,24,18,18,24,25,18,25,20,20,25,26,20,26,
22,4,6,27,4,27,24,24,27,28,24,28,25,25,28,29,25,29,26,6,30,27,27,30,31,27,31,28,28,31,32,28,32,29,30,
8,33,30,33,34,30,34,31,31,34,35,31,35,32,8,9,36,8,36,33,33,36,37,33,37,34,34,37,97,34,97,35,9,10,38,9,
38,36,36,38,39,36,39,37,37,39,40,37,40,97,10,12,41,10,41,38,38,41,42,38,42,39,39,42,43,39,43,40,12,14,
44,12,44,41,41,44,45,41,45,42,42,45,46,42,46,43,14,15,47,14,47,44,44,47,48,44,48,45,45,48,49,45,49,46,
15,17,50,15,50,47,47,50,51,47,51,48,48,51,52,48,52,49,17,2,19,17,19,50,50,19,21,50,21,51,51,21,23,51,
23,52,23,22,53,23,53,54,54,53,55,54,55,56,22,26,57,22,57,53,53,57,58,53,58,55,26,29,59,26,59,57,57,59,
58,58,59,60,29,32,61,29,61,59,59,61,62,59,62,60,32,35,63,32,63,61,61,63,77,61,77,62,35,97,64,35,64,63,
63,64,65,63,65,77,97,40,66,97,66,64,64,66,67,64,67,65,40,43,68,40,68,66,66,68,79,66,79,67,43,46,69,43,
69,68,68,69,70,68,70,79,46,49,71,46,71,69,69,71,72,69,72,70,49,52,73,49,73,71,71,73,81,71,81,72,52,23,
54,52,54,73,73,54,56,73,56,81,56,55,74,55,58,74,58,60,76,58,76,74,74,76,75,60,62,76,62,77,76,77,65,78,
77,78,76,76,78,75,65,67,78,67,79,78,79,70,80,79,80,78,78,80,75,70,72,80,72,81,80,81,56,74,81,74,80,80,
74,75,92,82,83,92,83,84,84,83,86,82,87,85,82,85,83,87,89,85,85,89,90,85,90,83,83,90,91,83,91,86,87,88,
89,88,92,93,88,93,89,89,93,90,90,93,101,90,101,91,93,92,84,93,84,101,84,86,94,84,94,96,96,94,95,96,95,
97,95,98,97,86,91,100,86,100,94,94,100,99,94,99,95,95,99,98,100,102,99,99,102,103,99,103,98,91,101,100,
100,101,102,101,84,96,101,96,102,102,96,97,102,97,103,104,105,106,104,106,107,107,106,108,107,108,109,
105,110,111,105,111,106,106,111,112,106,112,108,108,112,113,110,114,115,110,115,111,111,115,116,111,116,
112,112,116,122,112,122,113,114,117,118,114,118,115,115,118,119,115,119,116,116,119,123,116,123,122,117,
120,121,117,121,118,118,121,119,119,121,123,120,104,107,120,107,121,121,107,109,121,109,123,124,126,129,
124,125,126,127,125,124,125,127,126,127,129,126,128,127,124,127,128,129,128,124,129,129,126,130,130,131,
133,133,131,132,131,134,132,126,135,130,130,135,136,130,136,131,131,136,134,135,137,136,136,137,138,137,
139,138,126,140,135,135,140,141,135,141,137,137,141,139,126,129,140,140,142,141,141,142,143,142,144,143,
129,146,140,140,146,145,140,145,142,142,145,144,146,147,145,145,147,148,147,149,148,129,130,146,146,130,
133,146,133,147,147,133,149,
};
PROGMEM const int16_t facenormals[NTRIANGLES*3]={
11,126,-4,2,126,12,1,126,8,3,126,12,2,126,8,-34,65,103,-74,63,81,-2,126,-12,-2,126,-11,-3,126,-12,-4,
126,-11,12,126,-2,11,126,-2,12,126,-3,111,53,30,112,51,29,115,42,30,115,42,30,121,19,32,121,19,32,82,
52,81,81,52,81,84,42,84,84,42,84,88,19,88,88,19,88,29,51,112,29,51,112,30,42,115,30,42,115,32,19,121,
32,19,121,-28,51,112,-31,44,114,-30,42,115,-32,19,121,-32,19,121,-82,53,80,-83,42,85,-84,44,84,-88,19,
88,-88,19,88,-111,52,29,-111,52,29,-115,42,30,-115,42,30,-121,19,32,-121,19,32,-111,53,-30,-111,51,-29,
-115,42,-30,-115,42,-30,-121,19,-32,-121,18,-32,-82,52,-81,-81,52,-81,-84,42,-84,-84,42,-84,-88,19,-88,
-88,19,-88,-29,51,-112,-29,51,-112,-30,42,-115,-30,42,-115,-32,19,-121,-32,19,-121,30,53,-111,29,51,-112,
30,42,-115,30,42,-115,32,19,-121,32,19,-121,81,52,-82,81,52,-81,84,42,-84,84,42,-84,88,19,-88,88,19,-88,
112,51,-29,112,51,-29,115,42,-30,115,42,-30,121,19,-32,121,19,-32,116,-40,30,116,-39,30,88,-88,23,88,
-88,23,85,-40,85,85,-40,85,64,-88,64,64,-88,64,30,-40,116,30,-39,116,23,-87,88,23,-88,88,-30,-40,116,
-30,-39,116,-23,-88,88,-23,-88,88,-85,-40,85,-85,-40,85,-64,-88,64,-64,-88,64,-116,-40,30,-116,-39,30,
-88,-88,23,-88,-88,23,-116,-40,-30,-116,-39,-30,-88,-88,-23,-88,-88,-23,-85,-40,-85,-85,-40,-85,-64,-88,
-64,-64,-88,-64,-30,-40,-116,-30,-39,-116,-23,-88,-88,-23,-88,-88,30,-40,-116,30,-39,-116,23,-88,-88,
23,-88,-88,85,-40,-85,85,-40,-85,64,-88,-64,64,-88,-64,116,-40,-30,116,-39,-30,88,-88,-23,88,-88,-23,
23,-124,6,13,-125,13,3,-126,13,4,-126,10,1,-126,3,-6,-124,23,-13,-125,13,-13,-126,3,-10,-126,4,-3,-126,
1,-23,-124,-6,-13,-125,-13,-3,-126,-13,-4,-126,-10,-1,-126,-3,6,-124,-23,13,-125,-13,13,-126,-3,10,-126,
-4,3,-126,-1,4,-125,17,17,-104,69,105,-35,60,8,64,109,1,12,126,-6,124,26,-26,121,26,-31,116,37,-105,57,
41,-106,42,54,3,125,-18,12,-88,-90,-11,83,-95,-19,88,-88,-47,30,-113,-47,30,-113,8,-110,-62,105,-67,20,
88,24,88,91,22,85,80,74,63,61,77,79,65,51,95,-115,-28,45,-112,-32,49,-94,-75,37,-83,-78,54,-63,-100,44,
-84,-81,-48,-63,-96,-52,-58,-109,-26,-72,-18,-102,-62,-24,-107,96,22,-79,108,54,-36,63,83,-70,61,93,-59,
-38,108,52,-36,111,48,-105,58,41,-103,54,49,11,0,126,11,5,126,28,14,122,22,20,123,1,15,125,58,-101,49,
58,-101,48,114,-40,36,112,-32,48,88,-76,48,82,-56,78,58,-101,-49,58,-101,-48,116,-36,-35,110,-39,-48,
96,-66,-49,75,-65,-78,14,0,-126,8,5,-126,26,15,-123,84,-55,-77,-35,109,-53,-40,110,-48,-108,53,-38,-53,
63,-96,107,-66,11,53,-24,112,-16,125,4,-105,-64,30,-87,-91,-9,-4,125,-15,-33,-36,-116,113,-56,-3,28,123,
3,26,123,8,38,119,16,47,108,47,14,105,68,4,125,20,2,125,19,19,116,47,-8,124,25,-16,119,38,-47,108,47,
-41,119,6,-20,125,3,-20,125,2,-47,116,19,-30,123,-3,-25,124,-8,-38,119,-16,-47,108,-47,-12,112,-58,-4,
125,-21,-2,125,-20,-19,116,-47,8,123,-26,16,119,-38,47,108,-47,42,119,-11,20,125,-5,19,125,-2,47,116,
-19,
};
#define NEDGES  404
PROGMEM const uint16_t edges[NEDGES*2]={
0,1,0,2,0,16,1,2,1,3,1,4,1,18,1,24,2,16,2,17,2,18,2,19,3,4,3,5,3,6,4,6,4,24,4,27,5,6,5,7,6,7,6,27,6,30,
7,8,7,30,8,9,8,30,8,33,8,36,9,10,9,36,9,38,10,11,10,12,10,38,10,41,11,12,11,13,11,14,12,14,12,41,12,44,
13,14,13,15,14,15,14,44,14,47,15,16,15,17,15,47,15,50,16,17,17,19,17,50,18,19,18,20,18,24,18,25,19,20,
19,21,19,50,20,21,20,22,20,25,20,26,21,22,21,23,21,50,21,51,22,23,22,26,22,53,22,57,23,51,23,52,23,53,
23,54,24,25,24,27,24,28,25,26,25,28,25,29,26,29,26,57,26,59,27,28,27,30,27,31,28,29,28,31,28,32,29,32,
29,59,29,61,30,31,30,33,30,34,31,32,31,34,31,35,32,35,32,61,32,63,33,34,33,36,33,37,34,35,34,37,34,97,
35,63,35,64,35,97,36,37,36,38,36,39,37,39,37,40,37,97,38,39,38,41,38,42,39,40,39,42,39,43,40,43,40,66,
40,68,40,97,41,42,41,44,41,45,42,43,42,45,42,46,43,46,43,68,43,69,44,45,44,47,44,48,45,46,45,48,45,49,
46,49,46,69,46,71,47,48,47,50,47,51,48,49,48,51,48,52,49,52,49,71,49,73,50,51,51,52,52,54,52,73,53,54,
53,55,53,57,53,58,54,55,54,56,54,73,55,56,55,58,55,74,56,73,56,74,56,81,57,58,57,59,58,59,58,60,58,74,
58,76,59,60,59,61,59,62,60,62,60,76,61,62,61,63,61,77,62,76,62,77,63,64,63,65,63,77,64,65,64,66,64,67,
64,97,65,67,65,77,65,78,66,67,66,68,66,79,66,97,67,78,67,79,68,69,68,70,68,79,69,70,69,71,69,72,70,72,
70,79,70,80,71,72,71,73,71,81,72,80,72,81,73,81,74,75,74,76,74,80,74,81,75,76,75,78,75,80,76,77,76,78,
77,78,78,79,78,80,79,80,80,81,82,83,82,85,82,87,82,92,83,84,83,85,83,86,83,90,83,91,83,92,84,86,84,92,
84,93,84,94,84,96,84,101,85,87,85,89,85,90,86,91,86,94,86,100,87,88,87,89,88,89,88,92,88,93,89,90,89,
93,90,91,90,93,90,101,91,100,91,101,92,93,93,101,94,95,94,96,94,99,94,100,95,96,95,97,95,98,95,99,96,
97,96,101,96,102,97,98,97,102,97,103,98,99,98,103,99,100,99,102,99,103,100,101,100,102,101,102,102,103,
104,105,104,106,104,107,104,120,105,106,105,110,105,111,106,107,106,108,106,111,106,112,107,108,107,109,
107,120,107,121,108,109,108,112,108,113,109,121,109,123,110,111,110,114,110,115,111,112,111,115,111,116,
112,113,112,116,112,122,113,122,114,115,114,117,114,118,115,116,115,118,115,119,116,119,116,122,116,123,
117,118,117,120,117,121,118,119,118,121,119,121,119,123,120,121,121,123,122,123,124,125,124,126,124,127,
124,128,124,129,125,126,125,127,126,127,126,129,126,130,126,135,126,140,127,128,127,129,128,129,129,130,
129,140,129,146,130,131,130,133,130,135,130,136,130,146,131,132,131,133,131,134,131,136,132,133,132,134,
133,146,133,147,133,149,134,136,135,136,135,137,135,140,135,141,136,137,136,138,137,138,137,139,137,141,
138,139,139,141,140,141,140,142,140,145,140,146,141,142,141,143,142,143,142,144,142,145,143,144,144,145,
145,146,145,147,145,148,146,147,147,148,147,149,148,149,
};

Model model_data;
void init_model() {
    model_data.NVertices     = NVERTICES;
    model_data.NFaces        = NTRIANGLES;
    model_data.NEdges        = NEDGES;
    model_data.vertices      = vertices;
    model_data.edges         = edges;
    model_data.faces         = triangles;
    model_data.vertexNormals = normals;
    model_data.faceNormals   = facenormals;
}
