cbuffer MatrixBuffer
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
};

struct VertexInputType
{
    float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

PixelInputType vsMain(VertexInputType input)
{
    PixelInputType output;
    input.position.w = 1.0f;

    output.position = mul(input.position, matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProj);
    
    output.tex = input.tex;
    output.normal = mul(input.normal, (float3x3)matWorld);
    output.normal = normalize(output.normal);

    return output;
}