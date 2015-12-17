#include "groundworkoutside.h"

Groundworkoutside::Groundworkoutside()
{

}

Groundworkoutside::~Groundworkoutside()
{

}


/*
float Groundworkoutside::factorialfunction(float x)
{
if (x == 0)
return 1;
return x * factorialfunction(x - 1);
}


float Groundworkoutside::cfunction(int countnumberi, int totalnumbern)
{

float n = factorialfunction(totalnumbern);
float i = factorialfunction(countnumberi);
float bot = factorialfunction(totalnumbern - 1);
float c = n / (i*bot);

return c;
}

float Groundworkoutside::bfunction(float  t)
{

float c = cfunction(countnumberi, totalnumbern);
float timet = t;
float timetpower = powf(t, countnumberi);
//float result = c*(timet^countnumberi)*((1 - t)^(totalnumbern));

return 0.0;
}

GsVec Groundworkoutside::eval_bezier(float t, const std::vector<GsVec>& ctrlpnts) //so this returns a vector.
{
//ctrlpnts will be is P.i
// Using 't', we need find algorithm for b.i(t) == lagrange
int sizeofctrlpnts = ctrlpnts.size();
float c = 0;

GsVec ft(0.0f, 0.0f, 0.0f);
//GsArray<GsVec> ft = (0.0f, 0.0f, 0.0f);
for (int i = 0; i <= sizeofctrlpnts; i++) //sum of f(t) = p.j * B.i,n
{
//C(n,i) = n!/(i!*(n-1)!
float ct = factorialfunction(sizeofctrlpnts);
float cb = factorialfunction(sizeofctrlpnts - i);
c = ct / (cb*(factorialfunction(i)));
//std::cout << "i = " << i << " : ct = " << ct << " : cb (n-1)!=s " << cb << " : sizeofctrlpnts = " << sizeofctrlpnts << "\n";

//for B(t)
float b1 = powf(t, i);
float b2 = powf((1 - t), (sizeofctrlpnts - i));
float b = c*b1*b2;
//std::cout << "i = " << i << " :: c = " << c << " b  = " << b << " b1 = " << b1 << " b2 = " << b2 << " b = " << b << "\n";
ft = ft + (ctrlpnts[i] * b);
}

return ft;
}
*/

void Groundworkoutside::init()
{
	// Load programs:
	_vshgou.load_and_compile(GL_VERTEX_SHADER, "../vsh_mcol_gouraud.glsl");
	_fshgou.load_and_compile(GL_FRAGMENT_SHADER, "../fsh_gouraud.glsl");
	_proggouraud.init_and_link(_vshgou, _fshgou);

	// Define buffers needed:
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(3);       // will use 3 buffers (P, N, and T)
	_proggouraud.uniform_locations(10); // 'will send 9 variables' changed to 10 for "Text1"
	_proggouraud.uniform_location(0, "vTransf");
	_proggouraud.uniform_location(1, "vProj");
	_proggouraud.uniform_location(2, "lPos");
	_proggouraud.uniform_location(3, "la");
	_proggouraud.uniform_location(4, "ld");
	_proggouraud.uniform_location(5, "ls");
	_proggouraud.uniform_location(6, "ka");
	_proggouraud.uniform_location(7, "ks");
	_proggouraud.uniform_location(8, "sh");
	_proggouraud.uniform_location(9, "Tex1"); // 

											  //for uploading image
	GsImage I;
	gsuint _texid;

	//merced.bmp   breezy.bmp southparkbmp.bmp southparkbusstop
		if (!I.load("../southparkbmp.bmp")) std::cout << "COULD NOT LOAD IMAGE!\n";
		glGenTextures(1, &_texid); // ids start at 1
		glBindTexture(GL_TEXTURE_2D, _texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, I.w(), I.h(), 0, GL_RGBA, GL_UNSIGNED_BYTE, I.data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glGenerateMipmap(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, 0);
		//glBindVertexArray(0);
		I.init(0, 0); // free image from CPU
	

	/*
	// Define buffers needed:
	set_program(prog);
	gen_vertex_arrays(1); // will use 1 vertex array
	gen_buffers(2);       // will use 2 buffers: one for coordinates and one for colors
	uniform_locations(2); // will send 2 variables: the 2 matrices below
	uniform_location(0, "vTransf");
	uniform_location(1, "vProj");
	*/
	
}

void Groundworkoutside::build(const GsArray<GsVec>& pnts) //build the topbot-less cylinder and put texture around for work. 
{
	//ah, we need to fix this so it connets 2 line at a time. ==P.push
	//so V0 to V1, V1 and V2, V2 and V3.... and so on since GL.LINES require 2 points.
	//

	Parray.size(0);// set size to zero, just in case
	T.size(0);

	for (int i = 0; i < pnts.size()-1; i++)
	{
		Parray.push() = pnts[i];
		Parray.push() = pnts[i + 1];
		Parray.push() = pnts[i] + GsVec(0.0f, 2.0f, 0.0f);

		////////////////////////////// comes oppsite
		Parray.push() = pnts[i + 1] + GsVec(0.0f, 2.0f, 0.0f);
		Parray.push() = pnts[i] + GsVec(0.0f, 2.0f, 0.0f);
		Parray.push() = pnts[i + 1];
	}


	float genius = Parray.size() / 6;

	
	for (int i = 0; i < (genius); i++)
	{
		float me = i;
		T.push() = (GsVec2(me / genius, 0))* -1;
		T.push() = (GsVec2((me + 1) / genius, 0))* -1;
		T.push() = (GsVec2(me / genius, 1))* -1;

		T.push() = (GsVec2(me / genius, 1))* -1;
		T.push() = (GsVec2((me + 1) / genius, 1))*-1;
		T.push() = (GsVec2((me + 1) / genius, 0))*-1;
	}



	_mtl.specular.set(255, 255, 255);
	_mtl.shininess = 8; // increase specular effect

	// send data to OpenGL buffers:
	glBindVertexArray(va[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//so glBindBuffer makes the buffer object active
	//glBufferData would send the data to it. 
	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*Parray.size(), Parray.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float)*N.size(), N.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
	glBufferData(GL_ARRAY_BUFFER, T.size() * 2 * sizeof(float), T.pt(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); // break the existing vertex array object binding.

	_numpoints = Parray.size();

}

void Groundworkoutside::draw(const GsMat& tr, const GsMat& pr, const GsLight& l)
{

	float f[4];
	float sh = (float)_mtl.shininess;
	if (sh<0.001f) sh = 64;

	glUseProgram(_proggouraud.id);
	glUniformMatrix4fv(_proggouraud.uniloc[0], 1, GL_FALSE, tr.e);
	glUniformMatrix4fv(_proggouraud.uniloc[1], 1, GL_FALSE, pr.e);
	glUniform3fv(_proggouraud.uniloc[2], 1, l.pos.e);
	glUniform4fv(_proggouraud.uniloc[3], 1, l.amb.get(f));
	glUniform4fv(_proggouraud.uniloc[4], 1, l.dif.get(f));
	glUniform4fv(_proggouraud.uniloc[5], 1, l.spe.get(f));
	glUniform4fv(_proggouraud.uniloc[6], 1, _mtl.ambient.get(f));
	glUniform4fv(_proggouraud.uniloc[7], 1, _mtl.specular.get(f));
	glUniform1fv(_proggouraud.uniloc[8], 1, &sh);
	//glUniform1fv(_proggouraud.uniloc[9], 1, &_texid);

	glBindVertexArray(va[0]);
	glDrawArrays(GL_TRIANGLES, 0, _numpoints);
	glBindVertexArray(0); // break the existing vertex array object binding.
}

