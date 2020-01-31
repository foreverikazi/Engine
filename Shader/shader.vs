cbuffer MatrixBuffer
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
};

//cbuffer CameraBuffer
//{
	//float3 cameraPosition;
	//float padding;
//};

struct VertexInputType
{
    float4 position : POSITION;
	float2 tex : TEXCOORD;
    float3 normal : NORMAL; 
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	//float3 viewDirection : TEXCOORD1;
};

PixelInputType vsMain(VertexInputType input)
{
    PixelInputType output;
    //float4 worldPosition;

    output.position = mul(input.position, matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProj);

    output.tex = input.tex;
    output.normal = mul(input.normal, (float3x3)matWorld); 
	output.normal = normalize(output.normal);

	//worldPosition = mul(input.position, matWorld);
	//output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	//output.viewDirection = normalize(output.viewDirection);

    return output;
}