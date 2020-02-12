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
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 tex : TEXCOORD0;
};

PixelInputType vsMain(VertexInputType input)
{
    PixelInputType output;

	input.position.w = 1.0f;

    output.position = mul(input.position, matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProj).xyww;

    output.tex = input.position;

    return output;
}