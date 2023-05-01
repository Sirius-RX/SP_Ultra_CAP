#include "IIR_FIlter.h"
#include "fmac.h"

//static int16_t firB[127] = { 255, 12, 11, 8, 5, 1, -4, -11, -18, -26, -35, -45, -55, -66, -77, -89, -100, -111, -121,
//        -130, -139, -146, -152, -156, -158, -158, -155, -150, -141, -130, -115, -97, -76, -51, -22, 10, 45, 83, 124,
//        169, 216, 265, 317, 370, 425, 481, 537, 593, 649, 704, 758, 810, 860, 908, 952, 993, 1030, 1062, 1091, 1114,
//        1133, 1146, 1154, 1157, 1154, 1146, 1133, 1114, 1091, 1062, 1030, 993, 952, 908, 860, 810, 758, 704, 649, 593,
//        537, 481, 425, 370, 317, 265, 216, 169, 124, 83, 45, 10, -22, -51, -76, -97, -115, -130, -141, -150, -155, -158,
//        -158, -156, -152, -146, -139, -130, -121, -111, -100, -89, -77, -66, -55, -45, -35, -26, -18, -11, -4, 1, 5, 8,
//        11, 12, 255 };

static int16_t iirA[2] = { 31754, 0 };
static int16_t iirB[3] = { 507, 507, 0 };

void HAL_FMAC_FilterConfig_my(void)
{
    /* declare a filter configuration structure */
    FMAC_FilterConfigTypeDef sFmacConfig;
    /* Set the coefficient buffer base address */
    sFmacConfig.CoeffBaseAddress = 0;
    /* Set the coefficient buffer size to the number of coeffs */
    sFmacConfig.CoeffBufferSize = 5;
    /* Set the Input buffer base address to the next free address */
    sFmacConfig.InputBaseAddress = 5;
    /* Set the input buffer size greater than the number of coeffs */
    sFmacConfig.InputBufferSize = 7;
    /* Set the input watermark to zero since we are using DMA */
    sFmacConfig.InputThreshold = FMAC_THRESHOLD_1;
    /* Set the Output buffer base address to the next free address */
    sFmacConfig.OutputBaseAddress = 12;
    /* Set the output buffer size */
    sFmacConfig.OutputBufferSize = 6;
    /* Set the output watermark to zero since we are using DMA */
    sFmacConfig.OutputThreshold = FMAC_THRESHOLD_1;
    /* No A coefficients since FIR */
    sFmacConfig.pCoeffA = iirA;
    /* Number of A coefficients */
    sFmacConfig.CoeffASize = 2;
    /* Pointer to the coefficients in memory */
    sFmacConfig.pCoeffB = iirB;
    /* Number of coefficients */
    sFmacConfig.CoeffBSize = 3;
    /* Select FIR filter function */
    sFmacConfig.Filter = FMAC_FUNC_IIR_DIRECT_FORM_1;
    /* Enable DMA input transfer */
    sFmacConfig.InputAccess = FMAC_BUFFER_ACCESS_NONE;
    /* Enable DMA output transfer */
    sFmacConfig.OutputAccess = FMAC_BUFFER_ACCESS_DMA;
    /* Enable clipping of the output at 0x7FFF and 0x8000 */
    sFmacConfig.Clip = FMAC_CLIP_ENABLED;
    /* P parameter contains number of B coefficients */
    sFmacConfig.P = 3;
    /* Q parameter contains number of A coefficients */
    sFmacConfig.Q = 2;
    /* R parameter contains the post-shift value */
    sFmacConfig.R = 0;
    /* Configure the FMAC */
    HAL_FMAC_FilterConfig(&hfmac, &sFmacConfig);
    uint16_t ExpectedCalculatedOutputSize = 1;
    HAL_FMAC_FilterStart(&hfmac, (int16_t*) &c_in.value_origin, &ExpectedCalculatedOutputSize);
}
