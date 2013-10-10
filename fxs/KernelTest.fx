RWTexture2D<float4> output : register(u0);

[numthreads(32, 32, 1)]
void main( 	
	uint3 blockID			: SV_GroupID,
	uint threadIDBlockIndex : SV_GroupIndex,
	uint3 threadIDDispatch	: SV_DispatchThreadID,
	uint3 threadIDBlock		: SV_GroupThreadID ) {
	output[ threadIDDispatch.xy ] = float4( 0.0f, 1.0f, 0.0f, 1.0f );
}