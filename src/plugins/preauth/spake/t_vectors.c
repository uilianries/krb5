/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/* plugins/preauth/spake/t_vectors.c - SPAKE test vector verification */
/*
 * Copyright (C) 2015 by the Massachusetts Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "k5-int.h"
#include "k5-hex.h"
#include "groups.h"
#include "iana.h"
#include "util.h"
#include <ctype.h>

struct test {
    krb5_enctype enctype;
    int32_t group;
    const char *ikey;
    const char *w;
    const char *x;
    const char *y;
    const char *T;
    const char *S;
    const char *K;
    const char *support;
    const char *challenge;
    const char *thash;
    const char *body;
    const char *K0;
    const char *K1;
    const char *K2;
    const char *K3;
} tests[] = {
    { ENCTYPE_DES3_CBC_SHA1, SPAKE_GROUP_EDWARDS25519,
      /* initial key, w, x, y, T, S, K */
      "850BB51358548CD05E86768C313E3BFEF7511937DCF72C3E",
      "686D84730CB8679AE95416C6567C6A63F2C9CEF124F7A3371AE81E11CAD42A37",
      "201012D07BFD48DDFA33C4AAC4FB1E229FB0D043CFE65EBFB14399091C71A723",
      "500B294797B8B042ACA1BEDC0F5931A4F52C537B3608B2D05CC8A2372F439F25",
      "18F511E750C97B592ACD30DB7D9E5FCA660389102E6BF610C1BFBED4616C8362",
      "5D10705E0D1E43D5DBF30240CCFBDE4A0230C70D4C79147AB0B317EDAD2F8AE7",
      "25BDE0D875F0FEB5755F45BA5E857889D916ECF7476F116AA31DC3E037EC4292",
      /* support, challenge, thash, body */
      "A0093007A0053003020101",
      "A1363034A003020101A122042018F511E750C97B592ACD30DB7D9E5FCA660389"
      "102E6BF610C1BFBED4616C8362A20930073005A003020101",
      "EAAA08807D0616026FF51C849EFBF35BA0CE3C5300E7D486DA46351B13D4605B",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020110",
      /* K'[0], K'[1], K'[2], K'[3] */
      "BAF12FAE7CD958CBF1A29BFBC71F89CE49E03E295D89DAFD",
      "64F73DD9C41908206BCEC1F719026B574F9D13463D7A2520",
      "0454520B086B152C455829E6BAEFF78A61DFE9E3D04A895D",
      "4A92260B25E3EF94C125D5C24C3E5BCED5B37976E67F25C4",
    },

    { ENCTYPE_ARCFOUR_HMAC, SPAKE_GROUP_EDWARDS25519,
      /* initial key, w, x, y, T, S, K */
      "8846F7EAEE8FB117AD06BDD830B7586C",
      "7C86659D29CF2B2EA93BFE79C3CEFB8850E82215B3EA6FCD896561D48048F49C",
      "C8A62E7B626F44CAD807B2D695450697E020D230A738C5CD5691CC781DCE8754",
      "18FE7C1512708C7FD06DB270361F04593775BC634CEAF45347E5C11C38AAE017",
      "7DB465F1C08C64983A19F560BCE966FE5306C4B447F70A5BCA14612A92DA1D63",
      "38F8D4568090148EBC9FD17C241B4CC2769505A7CA6F3F7104417B72B5B5CF54",
      "03E75EDD2CD7E7677642DD68736E91700953AC55DC650E3C2A1B3B4ACDB800F8",
      /* support, challenge, thash, body */
      "A0093007A0053003020101",
      "A1363034A003020101A12204207DB465F1C08C64983A19F560BCE966FE5306C4"
      "B447F70A5BCA14612A92DA1D63A20930073005A003020101",
      "F4B208458017DE6EF7F6A307D47D87DB6C2AF1D291B726860F68BC08BFEF440A",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020117",
      /* K'[0], K'[1], K'[2], K'[3] */
      "770B720C82384CBB693E85411EEDECBA",
      "621DEEC88E2865837C4D3462BB50A1D5",
      "1CC8F6333B9FA3B42662FD9914FBD5BB",
      "EDB4032B7FC3806D5211A534DCBC390C",
    },

    { ENCTYPE_AES128_CTS_HMAC_SHA1_96, SPAKE_GROUP_EDWARDS25519,
      /* initial key, w, x, y, T, S, K */
      "FCA822951813FB252154C883F5EE1CF4",
      "0D591B197B667E083C2F5F98AC891D3C9F99E710E464E62F1FB7C9B67936F3EB",
      "50BE049A5A570FA1459FB9F666E6FD80602E4E87790A0E567F12438A2C96C138",
      "B877AFE8612B406D96BE85BD9F19D423E95BE96C0E1E0B5824127195C3ED5917",
      "9E9311D985C1355E022D7C3C694AD8D6F7AD6D647B68A90B0FE46992818002DA",
      "FBE08F7F96CD5D4139E7C9ECCB95E79B8ACE41E270A60198C007DF18525B628E",
      "C2F7F99997C585E6B686CEB62DB42F17CC70932DEF3BB4CF009E36F22EA5473D",
      /* support, challenge, thash, body */
      "A0093007A0053003020101",
      "A1363034A003020101A12204209E9311D985C1355E022D7C3C694AD8D6F7AD6D"
      "647B68A90B0FE46992818002DAA20930073005A003020101",
      "951285F107C87F0169B9C918A1F51F60CB1A75B9F8BB799A99F53D03ADD94B5F",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020111",
      /* K'[0], K'[1], K'[2], K'[3] */
      "548022D58A7C47EAE8C49DCCF6BAA407",
      "B2C9BA0E13FC8AB3A9D96B51B601CF4A",
      "69F0EE5FDB6C237E7FCD38D9F87DF1BD",
      "78F91E2240B5EE528A5CC8D7CBEBFBA5",
    },
    { ENCTYPE_AES256_CTS_HMAC_SHA1_96, SPAKE_GROUP_EDWARDS25519,
      /* initial key, w, x, y, T, S, K */
      "01B897121D933AB44B47EB5494DB15E50EB74530DBDAE9B634D65020FF5D88C1",
      "E902341590A1B4BB4D606A1C643CCCB3F2108F1B6AA97B381012B9400C9E3F4E",
      "88C6C0A4F0241EF217C9788F02C32D00B72E4310748CD8FB5F94717607E6417D",
      "88B859DF58EF5C69BACDFE681C582754EAAB09A74DC29CFF50B328613C232F55",
      "6F301AACAE1220E91BE42868C163C5009AEEA1E9D9E28AFCFC339CDA5E7105B5",
      "9E2CC32908FC46273279EC75354B4AEAFA70C3D99A4D507175ED70D80B255DDA",
      "CF57F58F6E60169D2ECC8F20BB923A8E4C16E5BC95B9E64B5DC870DA7026321B",
      /* support, challenge, thash, body */
      "A0093007A0053003020101",
      "A1363034A003020101A12204206F301AACAE1220E91BE42868C163C5009AEEA1"
      "E9D9E28AFCFC339CDA5E7105B5A20930073005A003020101",
      "1C605649D4658B58CBE79A5FAF227ACC16C355C58B7DADE022F90C158FE5ED8E",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020112",
      /* K'[0], K'[1], K'[2], K'[3] */
      "A9BFA71C95C575756F922871524B65288B3F695573CCC0633E87449568210C23",
      "1865A9EE1EF0640EC28AC007391CAC624C42639C714767A974E99AA10003015F",
      "E57781513FEFDB978E374E156B0DA0C1A08148F5EB26B8E157AC3C077E28BF49",
      "008E6487293C3CC9FABBBCDD8B392D6DCB88222317FD7FE52D12FBC44FA047F1",
    },

#ifdef SPAKE_OPENSSL
    { ENCTYPE_AES256_CTS_HMAC_SHA1_96, SPAKE_GROUP_P256,
      /* initial key, w, x, y, T, S, K */
      "01B897121D933AB44B47EB5494DB15E50EB74530DBDAE9B634D65020FF5D88C1",
      "EB2984AF18703F94DD5288B8596CD36988D0D4E83BFB2B44DE14D0E95E2090BD",
      "935DDD725129FB7C6288E1A5CC45782198A6416D1775336D71EACD0549A3E80E",
      "E07405EB215663ABC1F254B8ADC0DA7A16FEBAA011AF923D79FDEF7C42930B33",
      "024F62078CEB53840D02612195494D0D0D88DE21FEEB81187C71CBF3D01E71788D",
      "021D07DC31266FC7CFD904CE2632111A169B7EC730E5F74A7E79700F86638E13C8",
      "0268489D7A9983F2FDE69C6E6A1307E9D252259264F5F2DFC32F58CCA19671E79B",
      /* support, challenge, thash, body */
      "A0093007A0053003020102",
      "A1373035A003020102A1230421024F62078CEB53840D02612195494D0D0D88DE"
      "21FEEB81187C71CBF3D01E71788DA20930073005A003020101",
      "20AD3C1A9A90FC037D1963A1C4BFB15AB4484D7B6CF07B12D24984F14652DE60",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020112",
      /* K'[0], K'[1], K'[2], K'[3] */
      "7D3B906F7BE49932DB22CD3463F032D06C9C078BE4B1D076D201FC6E61EF531E",
      "17D74E36F8993841FBB7FEB12FA4F011243D3AE4D2ACE55B39379294BBC4DB2C",
      "D192C9044081A2AA6A97A6C69E2724E8E5671C2C9CE073DD439CDBAF96D7DAB0",
      "41E5BAD6B67F12C53CE0E2720DD6A9887F877BF9463C2D5209C74C36F8D776B7",
    },

    { ENCTYPE_AES256_CTS_HMAC_SHA1_96, SPAKE_GROUP_P384,
      /* initial key, w, x, y, T, S, K */
      "01B897121D933AB44B47EB5494DB15E50EB74530DBDAE9B634D65020FF5D88C1",
      "0304CFC55151C6BBE889653DB96DBFE0BA4ACAFC024C1E8840CB3A486F6D80C1"
      "6E1B8974016AA4B7FA43042A9B3825B1",
      "F323CA74D344749096FD35D0ADF20806E521460637176E84D977E9933C49D76F"
      "CFC6E62585940927468FF53D864A7A50",
      "5B7C709ACB175A5AFB82860DEABCA8D0B341FACDFF0AC0F1A425799AA905D750"
      "7E1EA9C573581A81467437419466E472",
      "02A1524603EF14F184696F854229D3397507A66C63F841BA748451056BE07879"
      "AC298912387B1C5CDFF6381C264701BE57",
      "020D5ADFDB92BC377041CF5837412574C5D13E0F4739208A4F0C859A0A302BC6"
      "A533440A245B9D97A0D34AF5016A20053D",
      "0264AA8C61DA9600DFB0BEB5E46550D63740E4EF29E73F1A30D543EB43C25499"
      "037AD16538586552761B093CF0E37C703A",
      /* support, challenge, thash, body */
      "A0093007A0053003020103",
      "A1473045A003020103A133043102A1524603EF14F184696F854229D3397507A6"
      "6C63F841BA748451056BE07879AC298912387B1C5CDFF6381C264701BE57A209"
      "30073005A003020101",
      "5AC0D99EF9E5A73998797FE64F074673E3952DEC4C7D1AACCE8B75F64D2B0276"
      "A901CB8539B4E8ED69E4DB0CE805B47B",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020112",
      /* K'[0], K'[1], K'[2], K'[3] */
      "B917D37C16DD1D8567FBE379F64E1EE36CA3FD127AA4E60F97E4AFA3D9E56D91",
      "93D40079DAB229B9C79366829F4E7E7282E6A4B943AC7BAC69922D516673F49A",
      "BFC4F16F12F683E71589F9A888E232875EF293AC9793DB6C919567CD7B94BCD4",
      "3630E2B5B99938E7506733141E8EC344166F6407E5FC2EF107C156E764D1BC20",
    },

    { ENCTYPE_AES256_CTS_HMAC_SHA1_96, SPAKE_GROUP_P521,
      /* initial key, w, x, y, T, S, K */
      "01B897121D933AB44B47EB5494DB15E50EB74530DBDAE9B634D65020FF5D88C1",
      "DE3A095A2B2386EFF3EB15B735398DA1CAF95BC8425665D82370AFF58B0471F3"
      "4A57BCCDDF1EBF0A2965B58A93EE5B45E85D1A5435D1C8C83662999722D54283"
      "1F9A",
      "017C38701A14B490B6081DFC83524562BE7FBB42E0B20426465E3E37952D30BC"
      "AB0ED857010255D44936A1515607964A870C7C879B741D878F9F9CDF5A865306"
      "F3F5",
      "003E2E2950656FA231E959ACDD984D125E7FA59CEC98126CBC8F3888447911EB"
      "CD49428A1C22D5FDB76A19FBEB1D9EDFA3DA6CF55B158B53031D05D51433ADE9"
      "B2B4",
      "02017D3DE19A3EC53D0174905665EF37947D142535102CD9809C0DFBD0DFE007"
      "353D54CF406CE2A59950F2BB540DF6FBE75F8BBBEF811C9BA06CC275ADBD9675"
      "6696EC",
      "02004D142D87477841F6BA053C8F651F3395AD264B7405CA5911FB9A55ABD454"
      "FEF658A5F9ED97D1EFAC68764E9092FA15B9E0050880D78E95FD03ABF5931791"
      "6822B5",
      "03007C303F62F09282CC849490805BD4457A6793A832CBEB55DF427DB6A31E99"
      "B055D5DC99756D24D47B70AD8B6015B0FB8742A718462ED423B90FA3FE631AC1"
      "3FA916",
      /* support, challenge, thash, body */
      "A0093007A0053003020104",
      "A1593057A003020104A145044302017D3DE19A3EC53D0174905665EF37947D14"
      "2535102CD9809C0DFBD0DFE007353D54CF406CE2A59950F2BB540DF6FBE75F8B"
      "BBEF811C9BA06CC275ADBD96756696ECA20930073005A003020101",
      "8D6A89AE4D80CC4E47B6F4E48EA3E57919CC69598D0D3DC7C8BD49B6F1DB1409"
      "CA0312944CD964E213ABA98537041102237CFF5B331E5347A0673869B412302E",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020112",
      /* K'[0], K'[1], K'[2], K'[3] */
      "1EB3D10BEE8FAB483ADCD3EB38F3EBF1F4FEB8DB96ECC035F563CF2E1115D276",
      "482B92781CE57F49176E4C94153CC622FE247A7DBE931D1478315F856F085890",
      "A2C215126DD3DF280AAB5A27E1E0FB7E594192CBFF8D6D8E1B6F1818D9BB8FAC",
      "CC06603DE984324013A01F888DE6D43B410A4DA2DEA53509F30E433C352FB668",
    },
#endif /* SPAKE_OPENSSL */

    /* Successful optimistic challenge (no support message in transcript) */
    { ENCTYPE_AES256_CTS_HMAC_SHA1_96, SPAKE_GROUP_EDWARDS25519,
      /* initial key, w, x, y, T, S, K */
      "01B897121D933AB44B47EB5494DB15E50EB74530DBDAE9B634D65020FF5D88C1",
      "E902341590A1B4BB4D606A1C643CCCB3F2108F1B6AA97B381012B9400C9E3F4E",
      "70937207344CAFBC53C8A55070E399C584CBAFCE00B836980DD4E7E74FAD2A64",
      "785D6801A2490DF028903AC6449B105F2FF0DB895B252953CDC2076649526103",
      "83523B35F1565006CBFC4F159885467C2FB9BC6FE23D36CB1DA43D199F1A3118",
      "2A8F70F46CEE9030700037B77F22CEC7970DCC238E3E066D9D726BAF183992C6",
      "D3C5E4266AA6D1B2873A97CE8AF91C7E4D7A7AC456ACCED7908D34C561AD8FA6",
      /* support, challenge, thash, body */
      NULL,
      "A1363034A003020101A122042083523B35F1565006CBFC4F159885467C2FB9BC"
      "6FE23D36CB1DA43D199F1A3118A20930073005A003020101",
      "26F07F9F8965307434D11EA855461D41E0CBABCC0A1BAB48ECEE0C6C1A4292B7",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020112",
      /* K'[0], K'[1], K'[2], K'[3] */
      "4569EC08B5DE5C3CC19D941725913ACE8D74524B521A341DC746ACD5C3784D92",
      "0D96CE1A4AC0F2E280A0CFC31742B06461D83D04AE45433DB2D80478DD882A4C",
      "58018C19315A1BA5D5BB9813B58029F0AEC18A6F9CA59E0847DE1C60BC25945C",
      "ED7E9BFFD68C54D86FB19CD3C03F317F88A71AD9A5E94C28581D93FC4EC72B6A",
    },

#ifdef SPAKE_OPENSSL
    /* Rejected optimistic challenge (no support message in transcript),
     * falling back from edwards25519 to P-521 */
    { ENCTYPE_AES256_CTS_HMAC_SHA1_96, SPAKE_GROUP_P521,
      /* initial key, w, x, y, T, S, K */
      "01B897121D933AB44B47EB5494DB15E50EB74530DBDAE9B634D65020FF5D88C1",
      "DE3A095A2B2386EFF3EB15B735398DA1CAF95BC8425665D82370AFF58B0471F3"
      "4A57BCCDDF1EBF0A2965B58A93EE5B45E85D1A5435D1C8C83662999722D54283"
      "1F9A",
      "01687B59051BF40048D7C31D5A973D792FA12284B7A447E7F5938B5885CA0BB2"
      "C3F0BD30291A55FEA08E143E2E04BDD7D19B753C7C99032F06CAB0D9C2AA8F83"
      "7EF7",
      "01DED675EBF74FE30C9A53710F577E9CF84F09F6048FE245A4600004884CC167"
      "733F9A9E43108FB83BABE8754CD37CBD7025E28BC9FF870F084C7244F536285E"
      "25B4",
      "02014CB2E5B592ECE5990F0EF30D308C061DE1598BC4272B4A6599BED466FD15"
      "21693642ABCF4DBE36CE1A2D13967DE45F6C4F8D0FA8E14428BF03FB96EF5F1E"
      "D3E645",
      "02016C64995E804416F748FD5FA3AA678CBC7CBB596A4F523132DC8AF7CE84E5"
      "41F484A2C74808C6B21DCF7775BAEFA6753398425BECC7B838B210AC5DAA0CB0"
      "B710E2",
      "0200997F4848AE2E7A98C23D14AC662030743AB37FCCC2A45F1C721114F40BCC"
      "80FE6EC6ABA49868F8AEA1AA994D50E81B86D3E4D3C1130C8695B68907C673D9"
      "E5886A",
      /* support, challenge, thash, body */
      "A0093007A0053003020104",
      "A1593057A003020104A145044302014CB2E5B592ECE5990F0EF30D308C061DE1"
      "598BC4272B4A6599BED466FD1521693642ABCF4DBE36CE1A2D13967DE45F6C4F"
      "8D0FA8E14428BF03FB96EF5F1ED3E645A20930073005A003020101",
      "D0EFED5E3E2C39C26034756D92A66FEC3082AD793D0197F3F89AD36026F146A3"
      "996E548AA3FC49E2E82F8CAC5D132C505AA475B39E7BE79CDED22C26C41AA777",
      "3075A00703050000000000A1143012A003020101A10B30091B07726165627572"
      "6EA2101B0E415448454E412E4D49542E454455A3233021A003020102A11A3018"
      "1B066B72627467741B0E415448454E412E4D49542E454455A511180F31393730"
      "303130313030303030305AA703020100A8053003020112",
      /* K'[0], K'[1], K'[2], K'[3] */
      "631FCC8596E7F40E59045950D72AA0B7BAC2810A07B767050E983841CF3A2D4C",
      "881464920117074DBC67155A8F3341D1121EF65F78EA0380BFA81A134C1C47B1",
      "377B72AC3AF2CAAD582D73AE4682FD56B531EE56706200DD6C38C42B8219837A",
      "35AD8E4D580ED3F0D15AD928329773C081BD19F9A56363F3A5F77C7E66108C26",
    },
#endif /* SPAKE_OPENSSL */
};

static krb5_context ctx;

static void
check(krb5_error_code code)
{
    const char *errmsg;

    if (code) {
        errmsg = krb5_get_error_message(ctx, code);
        assert(errmsg != NULL);
        abort();
    }
}

static void
check_key_equal(const krb5_keyblock *kb1, const krb5_keyblock *kb2)
{
    assert(kb1->enctype == kb2->enctype);
    assert(kb1->length == kb2->length);
    assert(memcmp(kb1->contents, kb2->contents, kb1->length) == 0);
}

static krb5_data *
decode_data(const char *s)
{
    uint8_t *bytes;
    size_t len;
    krb5_data *d;

    if (k5_hex_decode(s, &bytes, &len) != 0)
        abort();
    d = malloc(sizeof(*d));
    assert(d != NULL);
    *d = make_data(bytes, len);
    return d;
}

static krb5_keyblock *
decode_keyblock(krb5_enctype enctype, const char *s)
{
    uint8_t *bytes;
    size_t len;
    krb5_keyblock *kb;

    if (k5_hex_decode(s, &bytes, &len) != 0)
        abort();
    kb = malloc(sizeof(*kb));
    kb->magic = KV5M_KEYBLOCK;
    kb->enctype = enctype;
    kb->length = len;
    kb->contents = bytes;
    return kb;
}

static void
run_test(const struct test *t)
{
    groupstate *gstate;
    krb5_keyblock *ikey, *K0, *K1, *K2, *K3, *kb;
    krb5_data *w, *x, *y, *T, *S, *K, *support, *challenge, *thash;
    krb5_data *body, wbytes, result, hash, empty = empty_data();

    /* Decode hex strings into keyblocks and byte strings. */
    ikey = decode_keyblock(t->enctype, t->ikey);
    w = decode_data(t->w);
    x = decode_data(t->x);
    y = decode_data(t->y);
    T = decode_data(t->T);
    S = decode_data(t->S);
    K = decode_data(t->K);
    support = (t->support != NULL) ? decode_data(t->support) : NULL;
    challenge = decode_data(t->challenge);
    thash = decode_data(t->thash);
    body = decode_data(t->body);
    K0 = decode_keyblock(t->enctype, t->K0);
    K1 = decode_keyblock(t->enctype, t->K1);
    K2 = decode_keyblock(t->enctype, t->K2);
    K3 = decode_keyblock(t->enctype, t->K3);

    check(derive_wbytes(ctx, t->group, ikey, &wbytes));
    assert(data_eq(*w, wbytes));

    /* Verify KDC-side result computation. */
    check(group_init_state(ctx, TRUE, &gstate));
    check(group_result(ctx, gstate, t->group, &wbytes, x, S, &result));
    assert(data_eq(*K, result));
    krb5_free_data_contents(ctx, &result);
    group_free_state(gstate);

    /* Verify client-side result computation. */
    check(group_init_state(ctx, FALSE, &gstate));
    check(group_result(ctx, gstate, t->group, &wbytes, y, T, &result));
    assert(data_eq(*K, result));
    krb5_free_data_contents(ctx, &result);

    /* Verify transcript hash. */
    hash = empty_data();
    check(update_thash(ctx, gstate, t->group, &hash, support, challenge));
    check(update_thash(ctx, gstate, t->group, &hash, S, &empty));
    assert(data_eq(*thash, hash));
    krb5_free_data_contents(ctx, &hash);

    /* Verify derived keys. */
    check(derive_key(ctx, gstate, t->group, ikey, &wbytes, K, thash, body, 0,
                     &kb));
    check_key_equal(K0, kb);
    krb5_free_keyblock(ctx, kb);
    check(derive_key(ctx, gstate, t->group, ikey, &wbytes, K, thash, body, 1,
                     &kb));
    check_key_equal(K1, kb);
    krb5_free_keyblock(ctx, kb);
    check(derive_key(ctx, gstate, t->group, ikey, &wbytes, K, thash, body, 2,
                     &kb));
    check_key_equal(K2, kb);
    krb5_free_keyblock(ctx, kb);
    check(derive_key(ctx, gstate, t->group, ikey, &wbytes, K, thash, body, 3,
                     &kb));
    check_key_equal(K3, kb);
    krb5_free_keyblock(ctx, kb);

    group_free_state(gstate);
    krb5_free_data_contents(ctx, &wbytes);
    krb5_free_keyblock(ctx, ikey);
    krb5_free_data(ctx, w);
    krb5_free_data(ctx, x);
    krb5_free_data(ctx, y);
    krb5_free_data(ctx, T);
    krb5_free_data(ctx, S);
    krb5_free_data(ctx, K);
    krb5_free_data(ctx, support);
    krb5_free_data(ctx, challenge);
    krb5_free_data(ctx, thash);
    krb5_free_data(ctx, body);
    krb5_free_keyblock(ctx, K0);
    krb5_free_keyblock(ctx, K1);
    krb5_free_keyblock(ctx, K2);
    krb5_free_keyblock(ctx, K3);
}

int
main(void)
{
    size_t i;

    check(krb5_init_context(&ctx));
    for (i = 0; i < sizeof(tests) / sizeof(*tests); i++)
        run_test(&tests[i]);
    krb5_free_context(ctx);
    return 0;
}
