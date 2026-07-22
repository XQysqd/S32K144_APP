/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/*!
 * @file flash_driver.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, Global typedef not referenced.
 * flash_swap_callback_t can be used in user code.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * This is required to enable the use of a macro needed by
 * the user code (even if the macro is not used inside the flash driver code)
 * or driver code in the future.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Directive 4.9, Function-like macro defined.
 * This macro is needed in creating a common name for any IP.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 11.4, Conversion between a pointer and
 * integer type.
 * The cast is required to initialize a pointer with an unsigned long define,
 * representing an address.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.6, Cast from unsigned int to pointer.
 * The cast is required to initialize a pointer with an unsigned long define,
 * representing an address.
 */

#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include <stdbool.h>
#include <stddef.h>
#include "status.h"
#include "device_registers.h"

/*!
 * @defgroup flash_driver Flash Memory (Flash)
 * @ingroup flash
 * @details This section describes the programming interface of the Flash Peripheral Driver.
 * @{
 */

/*******************************************************************************
 * FTFx - Register instance definitions
 * FTFx - 寄存器实例定义
 *******************************************************************************/
/*******************************************************************************
 * FTFE
 *******************************************************************************/
#ifdef FTFE
/* FTFE 基地址映射 */
#define FTFx_BASE                               FTFE_BASE
#define FTFx_FSTAT                              FTFE->FSTAT
#define FTFx_FCNFG                              FTFE->FCNFG
#define FTFx_FSEC                               FTFE->FSEC
#define FTFx_FOPT                               FTFE->FOPT
/* FTFE FCCOB 命令参数寄存器阵列映射 */
#define FTFx_FCCOB3                             FTFE->FCCOB[0]
#define FTFx_FCCOB2                             FTFE->FCCOB[1]
#define FTFx_FCCOB1                             FTFE->FCCOB[2]
#define FTFx_FCCOB0                             FTFE->FCCOB[3]
#define FTFx_FCCOB7                             FTFE->FCCOB[4]
#define FTFx_FCCOB6                             FTFE->FCCOB[5]
#define FTFx_FCCOB5                             FTFE->FCCOB[6]
#define FTFx_FCCOB4                             FTFE->FCCOB[7]
#define FTFx_FCCOBB                             FTFE->FCCOB[8]
#define FTFx_FCCOBA                             FTFE->FCCOB[9]
#define FTFx_FCCOB9                             FTFE->FCCOB[10]
#define FTFx_FCCOB8                             FTFE->FCCOB[11]
/* FTFE 保护寄存器映射 */
#define FTFx_FPROT3                             FTFE->FPROT[0]
#define FTFx_FPROT2                             FTFE->FPROT[1]
#define FTFx_FPROT1                             FTFE->FPROT[2]
#define FTFx_FPROT0                             FTFE->FPROT[3]
#define FTFx_FEPROT                             FTFE->FEPROT
#define FTFx_FDPROT                             FTFE->FDPROT
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT                            FTFE->FERSTAT
#define FTFx_FERCNFG                            FTFE->FERCNFG
#endif
/* FSTAT 状态寄存器位域定义 */
#define FTFx_FSTAT_MGSTAT0_MASK                 FTFE_FSTAT_MGSTAT0_MASK
#define FTFx_FSTAT_MGSTAT0_SHIFT                FTFE_FSTAT_MGSTAT0_SHIFT
#define FTFx_FSTAT_MGSTAT0_WIDTH                FTFE_FSTAT_MGSTAT0_WIDTH
#define FTFx_FSTAT_MGSTAT0(x)                   FTFE_FSTAT_MGSTAT0(x)
#define FTFx_FSTAT_FPVIOL_MASK                  FTFE_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_FPVIOL_SHIFT                 FTFE_FSTAT_FPVIOL_SHIFT
#define FTFx_FSTAT_FPVIOL_WIDTH                 FTFE_FSTAT_FPVIOL_WIDTH
#define FTFx_FSTAT_FPVIOL(x)                    FTFE_FSTAT_FPVIOL(x)
#define FTFx_FSTAT_ACCERR_MASK                  FTFE_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_ACCERR_SHIFT                 FTFE_FSTAT_ACCERR_SHIFT
#define FTFx_FSTAT_ACCERR_WIDTH                 FTFE_FSTAT_ACCERR_WIDTH
#define FTFx_FSTAT_ACCERR(x)                    FTFE_FSTAT_ACCERR(x)
#define FTFx_FSTAT_RDCOLERR_MASK                FTFE_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_RDCOLERR_SHIFT               FTFE_FSTAT_RDCOLERR_SHIFT
#define FTFx_FSTAT_RDCOLERR_WIDTH               FTFE_FSTAT_RDCOLERR_WIDTH
#define FTFx_FSTAT_RDCOLERR(x)                  FTFE_FSTAT_RDCOLERR(x)
#define FTFx_FSTAT_CCIF_MASK                    FTFE_FSTAT_CCIF_MASK
#define FTFx_FSTAT_CCIF_SHIFT                   FTFE_FSTAT_CCIF_SHIFT
#define FTFx_FSTAT_CCIF_WIDTH                   FTFE_FSTAT_CCIF_WIDTH
#define FTFx_FSTAT_CCIF(x)                      FTFE_FSTAT_CCIF(x)
/* FCNFG 配置寄存器位域定义 */
#define FTFx_FCNFG_EEERDY_MASK                  FTFE_FCNFG_EEERDY_MASK
#define FTFx_FCNFG_EEERDY_SHIFT                 FTFE_FCNFG_EEERDY_SHIFT
#define FTFx_FCNFG_EEERDY_WIDTH                 FTFE_FCNFG_EEERDY_WIDTH
#define FTFx_FCNFG_EEERDY(x)                    FTFE_FCNFG_EEERDY(x)
#define FTFx_FCNFG_RAMRDY_MASK                  FTFE_FCNFG_RAMRDY_MASK
#define FTFx_FCNFG_RAMRDY_SHIFT                 FTFE_FCNFG_RAMRDY_SHIFT
#define FTFx_FCNFG_RAMRDY_WIDTH                 FTFE_FCNFG_RAMRDY_WIDTH
#define FTFx_FCNFG_RAMRDY(x)                    FTFE_FCNFG_RAMRDY(x)
#define FTFx_FCNFG_PFLSH_MASK                   FTFE_FCNFG_PFLSH_MASK
#define FTFx_FCNFG_PFLSH_SHIFT                  FTFE_FCNFG_PFLSH_SHIFT
#define FTFx_FCNFG_PFLSH_WIDTH                  FTFE_FCNFG_PFLSH_WIDTH
#define FTFx_FCNFG_PFLSH(x)                     FTFE_FCNFG_PFLSH(x)
#define FTFx_FCNFG_ERSSUSP_MASK                 FTFE_FCNFG_ERSSUSP_MASK
#define FTFx_FCNFG_ERSSUSP_SHIFT                FTFE_FCNFG_ERSSUSP_SHIFT
#define FTFx_FCNFG_ERSSUSP_WIDTH                FTFE_FCNFG_ERSSUSP_WIDTH
#define FTFx_FCNFG_ERSSUSP(x)                   FTFE_FCNFG_ERSSUSP(x)
#define FTFx_FCNFG_ERSAREQ_MASK                 FTFE_FCNFG_ERSAREQ_MASK
#define FTFx_FCNFG_ERSAREQ_SHIFT                FTFE_FCNFG_ERSAREQ_SHIFT
#define FTFx_FCNFG_ERSAREQ_WIDTH                FTFE_FCNFG_ERSAREQ_WIDTH
#define FTFx_FCNFG_ERSAREQ(x)                   FTFE_FCNFG_ERSAREQ(x)
#define FTFx_FCNFG_RDCOLLIE_MASK                FTFE_FCNFG_RDCOLLIE_MASK
#define FTFx_FCNFG_RDCOLLIE_SHIFT               FTFE_FCNFG_RDCOLLIE_SHIFT
#define FTFx_FCNFG_RDCOLLIE_WIDTH               FTFE_FCNFG_RDCOLLIE_WIDTH
#define FTFx_FCNFG_RDCOLLIE(x)                  FTFE_FCNFG_RDCOLLIE(x)
#define FTFx_FCNFG_CCIE_MASK                    FTFE_FCNFG_CCIE_MASK
#define FTFx_FCNFG_CCIE_SHIFT                   FTFE_FCNFG_CCIE_SHIFT
#define FTFx_FCNFG_CCIE_WIDTH                   FTFE_FCNFG_CCIE_WIDTH
#define FTFx_FCNFG_CCIE(x)                      FTFE_FCNFG_CCIE(x)
/* FSEC 安全寄存器位域定义 */
#define FTFx_FSEC_SEC_MASK                      FTFE_FSEC_SEC_MASK
#define FTFx_FSEC_SEC_SHIFT                     FTFE_FSEC_SEC_SHIFT
#define FTFx_FSEC_SEC_WIDTH                     FTFE_FSEC_SEC_WIDTH
#define FTFx_FSEC_SEC(x)                        FTFE_FSEC_SEC(x)
#define FTFx_FSEC_FSLACC_MASK                   FTFE_FSEC_FSLACC_MASK
#define FTFx_FSEC_FSLACC_SHIFT                  FTFE_FSEC_FSLACC_SHIFT
#define FTFx_FSEC_FSLACC_WIDTH                  FTFE_FSEC_FSLACC_WIDTH
#define FTFx_FSEC_FSLACC(x)                     FTFE_FSEC_FSLACC(x)
#define FTFx_FSEC_MEEN_MASK                     FTFE_FSEC_MEEN_MASK
#define FTFx_FSEC_MEEN_SHIFT                    FTFE_FSEC_MEEN_SHIFT
#define FTFx_FSEC_MEEN_WIDTH                    FTFE_FSEC_MEEN_WIDTH
#define FTFx_FSEC_MEEN(x)                       FTFE_FSEC_MEEN(x)
#define FTFx_FSEC_KEYEN_MASK                    FTFE_FSEC_KEYEN_MASK
#define FTFx_FSEC_KEYEN_SHIFT                   FTFE_FSEC_KEYEN_SHIFT
#define FTFx_FSEC_KEYEN_WIDTH                   FTFE_FSEC_KEYEN_WIDTH
#define FTFx_FSEC_KEYEN(x)                      FTFE_FSEC_KEYEN(x)
/* FOPT 选项寄存器位域定义 */
#define FTFx_FOPT_OPT_MASK                      FTFE_FOPT_OPT_MASK
#define FTFx_FOPT_OPT_SHIFT                     FTFE_FOPT_OPT_SHIFT
#define FTFx_FOPT_OPT_WIDTH                     FTFE_FOPT_OPT_WIDTH
#define FTFx_FOPT_OPT(x)                        FTFE_FOPT_OPT(x)
/* FCCOB 通用命令参数寄存器位域定义 */
#define FTFx_FCCOB_CCOBn_MASK                   FTFE_FCCOB_CCOBn_MASK
#define FTFx_FCCOB_CCOBn_SHIFT                  FTFE_FCCOB_CCOBn_SHIFT
#define FTFx_FCCOB_CCOBn_WIDTH                  FTFE_FCCOB_CCOBn_WIDTH
#define FTFx_FCCOB_CCOBn(x)                     FTFE_FCCOB_CCOBn(x)
/* FPROT 程序Flash保护寄存器位域定义 */
#define FTFx_FPROT_PROT_MASK                    FTFE_FPROT_PROT_MASK
#define FTFx_FPROT_PROT_SHIFT                   FTFE_FPROT_PROT_SHIFT
#define FTFx_FPROT_PROT_WIDTH                   FTFE_FPROT_PROT_WIDTH
#define FTFx_FPROT_PROT(x)                      FTFE_FPROT_PROT(x)
/* FEPROT EEPROM保护寄存器位域定义 */
#define FTFx_FEPROT_EPROT_MASK                  FTFE_FEPROT_EPROT_MASK
#define FTFx_FEPROT_EPROT_SHIFT                 FTFE_FEPROT_EPROT_SHIFT
#define FTFx_FEPROT_EPROT_WIDTH                 FTFE_FEPROT_EPROT_WIDTH
#define FTFx_FEPROT_EPROT(x)                    FTFE_FEPROT_EPROT(x)
/* FDPROT 数据Flash保护寄存器位域定义 */
#define FTFx_FDPROT_DPROT_MASK                  FTFE_FDPROT_DPROT_MASK
#define FTFx_FDPROT_DPROT_SHIFT                 FTFE_FDPROT_DPROT_SHIFT
#define FTFx_FDPROT_DPROT_WIDTH                 FTFE_FDPROT_DPROT_WIDTH
#define FTFx_FDPROT_DPROT(x)                    FTFE_FDPROT_DPROT(x)
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
/* FERSTAT ECC错误状态寄存器位域定义 */
#define FTFx_FERSTAT_DFDIF_MASK                 FTFE_FERSTAT_DFDIF_MASK
#define FTFx_FERSTAT_DFDIF_SHIFT                FTFE_FERSTAT_DFDIF_SHIFT
#define FTFx_FERSTAT_DFDIF_WIDTH                FTFE_FERSTAT_DFDIF_WIDTH
#define FTFx_FERSTAT_DFDIF(x)                   FTFE_FERSTAT_DFDIF(x)
/* FERCNFG ECC错误配置寄存器位域定义 */
#define FTFx_FERCNFG_DFDIE_MASK                 FTFE_FERCNFG_DFDIE_MASK
#define FTFx_FERCNFG_DFDIE_SHIFT                FTFE_FERCNFG_DFDIE_SHIFT
#define FTFx_FERCNFG_DFDIE_WIDTH                FTFE_FERCNFG_DFDIE_WIDTH
#define FTFx_FERCNFG_DFDIE(x)                   FTFE_FERCNFG_DFDIE(x)
#define FTFx_FERCNFG_FDFD_MASK                  FTFE_FERCNFG_FDFD_MASK
#define FTFx_FERCNFG_FDFD_SHIFT                 FTFE_FERCNFG_FDFD_SHIFT
#define FTFx_FERCNFG_FDFD_WIDTH                 FTFE_FERCNFG_FDFD_WIDTH
#define FTFx_FERCNFG_FDFD(x)                    FTFE_FERCNFG_FDFD(x)
#endif
/*******************************************************************************
 * FTFC — 针对 S32K1xx 系列 (FTFC 控制器)
 *******************************************************************************/
#elif defined(FTFC)
/* FTFC 基地址映射 */
#define FTFx_BASE                               FTFC_BASE
#define FTFx_FSTAT                              FTFC->FSTAT
#define FTFx_FCNFG                              FTFC->FCNFG
#define FTFx_FSEC                               FTFC->FSEC
#define FTFx_FOPT                               FTFC->FOPT
/* FTFC FCCOB 命令参数寄存器阵列映射 */
#define FTFx_FCCOB3                             FTFC->FCCOB[0]
#define FTFx_FCCOB2                             FTFC->FCCOB[1]
#define FTFx_FCCOB1                             FTFC->FCCOB[2]
#define FTFx_FCCOB0                             FTFC->FCCOB[3]
#define FTFx_FCCOB7                             FTFC->FCCOB[4]
#define FTFx_FCCOB6                             FTFC->FCCOB[5]
#define FTFx_FCCOB5                             FTFC->FCCOB[6]
#define FTFx_FCCOB4                             FTFC->FCCOB[7]
#define FTFx_FCCOBB                             FTFC->FCCOB[8]
#define FTFx_FCCOBA                             FTFC->FCCOB[9]
#define FTFx_FCCOB9                             FTFC->FCCOB[10]
#define FTFx_FCCOB8                             FTFC->FCCOB[11]
/* FTFC 保护寄存器映射 */
#define FTFx_FPROT3                             FTFC->FPROT[0]
#define FTFx_FPROT2                             FTFC->FPROT[1]
#define FTFx_FPROT1                             FTFC->FPROT[2]
#define FTFx_FPROT0                             FTFC->FPROT[3]
#define FTFx_FEPROT                             FTFC->FEPROT
#define FTFx_FDPROT                             FTFC->FDPROT
#define FTFx_FCSESTAT                           FTFC->FCSESTAT
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT                            FTFC->FERSTAT
#define FTFx_FERCNFG                            FTFC->FERCNFG
#endif
/* FSTAT 状态寄存器位域定义 */
#define FTFx_FSTAT_MGSTAT0_MASK                 FTFC_FSTAT_MGSTAT0_MASK
#define FTFx_FSTAT_MGSTAT0_SHIFT                FTFC_FSTAT_MGSTAT0_SHIFT
#define FTFx_FSTAT_MGSTAT0_WIDTH                FTFC_FSTAT_MGSTAT0_WIDTH
#define FTFx_FSTAT_MGSTAT0(x)                   FTFC_FSTAT_MGSTAT0(x)
#define FTFx_FSTAT_FPVIOL_MASK                  FTFC_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_FPVIOL_SHIFT                 FTFC_FSTAT_FPVIOL_SHIFT
#define FTFx_FSTAT_FPVIOL_WIDTH                 FTFC_FSTAT_FPVIOL_WIDTH
#define FTFx_FSTAT_FPVIOL(x)                    FTFC_FSTAT_FPVIOL(x)
#define FTFx_FSTAT_ACCERR_MASK                  FTFC_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_ACCERR_SHIFT                 FTFC_FSTAT_ACCERR_SHIFT
#define FTFx_FSTAT_ACCERR_WIDTH                 FTFC_FSTAT_ACCERR_WIDTH
#define FTFx_FSTAT_ACCERR(x)                    FTFC_FSTAT_ACCERR(x)
#define FTFx_FSTAT_RDCOLERR_MASK                FTFC_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_RDCOLERR_SHIFT               FTFC_FSTAT_RDCOLERR_SHIFT
#define FTFx_FSTAT_RDCOLERR_WIDTH               FTFC_FSTAT_RDCOLERR_WIDTH
#define FTFx_FSTAT_RDCOLERR(x)                  FTFC_FSTAT_RDCOLERR(x)
#define FTFx_FSTAT_CCIF_MASK                    FTFC_FSTAT_CCIF_MASK
#define FTFx_FSTAT_CCIF_SHIFT                   FTFC_FSTAT_CCIF_SHIFT
#define FTFx_FSTAT_CCIF_WIDTH                   FTFC_FSTAT_CCIF_WIDTH
#define FTFx_FSTAT_CCIF(x)                      FTFC_FSTAT_CCIF(x)
/* FCNFG 配置寄存器位域定义 */
#define FTFx_FCNFG_EEERDY_MASK                  FTFC_FCNFG_EEERDY_MASK
#define FTFx_FCNFG_EEERDY_SHIFT                 FTFC_FCNFG_EEERDY_SHIFT
#define FTFx_FCNFG_EEERDY_WIDTH                 FTFC_FCNFG_EEERDY_WIDTH
#define FTFx_FCNFG_EEERDY(x)                    FTFC_FCNFG_EEERDY(x)
#define FTFx_FCNFG_RAMRDY_MASK                  FTFC_FCNFG_RAMRDY_MASK
#define FTFx_FCNFG_RAMRDY_SHIFT                 FTFC_FCNFG_RAMRDY_SHIFT
#define FTFx_FCNFG_RAMRDY_WIDTH                 FTFC_FCNFG_RAMRDY_WIDTH
#define FTFx_FCNFG_RAMRDY(x)                    FTFC_FCNFG_RAMRDY(x)
#define FTFx_FCNFG_ERSSUSP_MASK                 FTFC_FCNFG_ERSSUSP_MASK
#define FTFx_FCNFG_ERSSUSP_SHIFT                FTFC_FCNFG_ERSSUSP_SHIFT
#define FTFx_FCNFG_ERSSUSP_WIDTH                FTFC_FCNFG_ERSSUSP_WIDTH
#define FTFx_FCNFG_ERSSUSP(x)                   FTFC_FCNFG_ERSSUSP(x)
#define FTFx_FCNFG_ERSAREQ_MASK                 FTFC_FCNFG_ERSAREQ_MASK
#define FTFx_FCNFG_ERSAREQ_SHIFT                FTFC_FCNFG_ERSAREQ_SHIFT
#define FTFx_FCNFG_ERSAREQ_WIDTH                FTFC_FCNFG_ERSAREQ_WIDTH
#define FTFx_FCNFG_ERSAREQ(x)                   FTFC_FCNFG_ERSAREQ(x)
#define FTFx_FCNFG_RDCOLLIE_MASK                FTFC_FCNFG_RDCOLLIE_MASK
#define FTFx_FCNFG_RDCOLLIE_SHIFT               FTFC_FCNFG_RDCOLLIE_SHIFT
#define FTFx_FCNFG_RDCOLLIE_WIDTH               FTFC_FCNFG_RDCOLLIE_WIDTH
#define FTFx_FCNFG_RDCOLLIE(x)                  FTFC_FCNFG_RDCOLLIE(x)
#define FTFx_FCNFG_CCIE_MASK                    FTFC_FCNFG_CCIE_MASK
#define FTFx_FCNFG_CCIE_SHIFT                   FTFC_FCNFG_CCIE_SHIFT
#define FTFx_FCNFG_CCIE_WIDTH                   FTFC_FCNFG_CCIE_WIDTH
#define FTFx_FCNFG_CCIE(x)                      FTFC_FCNFG_CCIE(x)
/* FSEC 安全寄存器位域定义 */
#define FTFx_FSEC_SEC_MASK                      FTFC_FSEC_SEC_MASK
#define FTFx_FSEC_SEC_SHIFT                     FTFC_FSEC_SEC_SHIFT
#define FTFx_FSEC_SEC_WIDTH                     FTFC_FSEC_SEC_WIDTH
#define FTFx_FSEC_SEC(x)                        FTFC_FSEC_SEC(x)
#define FTFx_FSEC_FSLACC_MASK                   FTFC_FSEC_FSLACC_MASK
#define FTFx_FSEC_FSLACC_SHIFT                  FTFC_FSEC_FSLACC_SHIFT
#define FTFx_FSEC_FSLACC_WIDTH                  FTFC_FSEC_FSLACC_WIDTH
#define FTFx_FSEC_FSLACC(x)                     FTFC_FSEC_FSLACC(x)
#define FTFx_FSEC_MEEN_MASK                     FTFC_FSEC_MEEN_MASK
#define FTFx_FSEC_MEEN_SHIFT                    FTFC_FSEC_MEEN_SHIFT
#define FTFx_FSEC_MEEN_WIDTH                    FTFC_FSEC_MEEN_WIDTH
#define FTFx_FSEC_MEEN(x)                       FTFC_FSEC_MEEN(x)
#define FTFx_FSEC_KEYEN_MASK                    FTFC_FSEC_KEYEN_MASK
#define FTFx_FSEC_KEYEN_SHIFT                   FTFC_FSEC_KEYEN_SHIFT
#define FTFx_FSEC_KEYEN_WIDTH                   FTFC_FSEC_KEYEN_WIDTH
#define FTFx_FSEC_KEYEN(x)                      FTFC_FSEC_KEYEN(x)
/* FOPT 选项寄存器位域定义 */
#define FTFx_FOPT_OPT_MASK                      FTFC_FOPT_OPT_MASK
#define FTFx_FOPT_OPT_SHIFT                     FTFC_FOPT_OPT_SHIFT
#define FTFx_FOPT_OPT_WIDTH                     FTFC_FOPT_OPT_WIDTH
#define FTFx_FOPT_OPT(x)                        FTFC_FOPT_OPT(x)
/* FCCOB 通用命令参数寄存器位域定义 */
#define FTFx_FCCOB_CCOBn_MASK                   FTFC_FCCOB_CCOBn_MASK
#define FTFx_FCCOB_CCOBn_SHIFT                  FTFC_FCCOB_CCOBn_SHIFT
#define FTFx_FCCOB_CCOBn_WIDTH                  FTFC_FCCOB_CCOBn_WIDTH
#define FTFx_FCCOB_CCOBn(x)                     FTFC_FCCOB_CCOBn(x)
/* FPROT 程序Flash保护寄存器位域定义 */
#define FTFx_FPROT_PROT_MASK                    FTFC_FPROT_PROT_MASK
#define FTFx_FPROT_PROT_SHIFT                   FTFC_FPROT_PROT_SHIFT
#define FTFx_FPROT_PROT_WIDTH                   FTFC_FPROT_PROT_WIDTH
#define FTFx_FPROT_PROT(x)                      FTFC_FPROT_PROT(x)
/* FEPROT EEPROM保护寄存器位域定义 */
#define FTFx_FEPROT_EPROT_MASK                  FTFC_FEPROT_EPROT_MASK
#define FTFx_FEPROT_EPROT_SHIFT                 FTFC_FEPROT_EPROT_SHIFT
#define FTFx_FEPROT_EPROT_WIDTH                 FTFC_FEPROT_EPROT_WIDTH
#define FTFx_FEPROT_EPROT(x)                    FTFC_FEPROT_EPROT(x)
/* FDPROT 数据Flash保护寄存器位域定义 */
#define FTFx_FDPROT_DPROT_MASK                  FTFC_FDPROT_DPROT_MASK
#define FTFx_FDPROT_DPROT_SHIFT                 FTFC_FDPROT_DPROT_SHIFT
#define FTFx_FDPROT_DPROT_WIDTH                 FTFC_FDPROT_DPROT_WIDTH
#define FTFx_FDPROT_DPROT(x)                    FTFC_FDPROT_DPROT(x)
/* FCSESTAT CSEc 安全状态寄存器位域定义 */
#define FTFx_FCSESTAT_IDB_MASK                  FTFC_FCSESTAT_IDB_MASK
#define FTFx_FCSESTAT_IDB_SHIFT                 FTFC_FCSESTAT_IDB_SHIFT
#define FTFx_FCSESTAT_IDB_WIDTH                 FTFC_FCSESTAT_IDB_WIDTH
#define FTFx_FCSESTAT_IDB(x)                    FTFC_FCSESTAT_IDB(x)
#define FTFx_FCSESTAT_EDB_MASK                  FTFC_FCSESTAT_EDB_MASK
#define FTFx_FCSESTAT_EDB_SHIFT                 FTFC_FCSESTAT_EDB_SHIFT
#define FTFx_FCSESTAT_EDB_WIDTH                 FTFC_FCSESTAT_EDB_WIDTH
#define FTFx_FCSESTAT_EDB(x)                    FTFC_FCSESTAT_EDB(x)
#define FTFx_FCSESTAT_RIN_MASK                  FTFC_FCSESTAT_RIN_MASK
#define FTFx_FCSESTAT_RIN_SHIFT                 FTFC_FCSESTAT_RIN_SHIFT
#define FTFx_FCSESTAT_RIN_WIDTH                 FTFC_FCSESTAT_RIN_WIDTH
#define FTFx_FCSESTAT_RIN(x)                    FTFC_FCSESTAT_RIN(x)
#define FTFx_FCSESTAT_BOK_MASK                  FTFC_FCSESTAT_BOK_MASK
#define FTFx_FCSESTAT_BOK_SHIFT                 FTFC_FCSESTAT_BOK_SHIFT
#define FTFx_FCSESTAT_BOK_WIDTH                 FTFC_FCSESTAT_BOK_WIDTH
#define FTFx_FCSESTAT_BOK(x)                    FTFC_FCSESTAT_BOK(x)
#define FTFx_FCSESTAT_BFN_MASK                  FTFC_FCSESTAT_BFN_MASK
#define FTFx_FCSESTAT_BFN_SHIFT                 FTFC_FCSESTAT_BFN_SHIFT
#define FTFx_FCSESTAT_BFN_WIDTH                 FTFC_FCSESTAT_BFN_WIDTH
#define FTFx_FCSESTAT_BFN(x)                    FTFC_FCSESTAT_BFN(x)
#define FTFx_FCSESTAT_BIN_MASK                  FTFC_FCSESTAT_BIN_MASK
#define FTFx_FCSESTAT_BIN_SHIFT                 FTFC_FCSESTAT_BIN_SHIFT
#define FTFx_FCSESTAT_BIN_WIDTH                 FTFC_FCSESTAT_BIN_WIDTH
#define FTFx_FCSESTAT_BIN(x)                    FTFC_FCSESTAT_BIN(x)
#define FTFx_FCSESTAT_SB_MASK                   FTFC_FCSESTAT_SB_MASK
#define FTFx_FCSESTAT_SB_SHIFT                  FTFC_FCSESTAT_SB_SHIFT
#define FTFx_FCSESTAT_SB_WIDTH                  FTFC_FCSESTAT_SB_WIDTH
#define FTFx_FCSESTAT_SB(x)                     FTFC_FCSESTAT_SB(x)
#define FTFx_FCSESTAT_BSY_MASK                  FTFC_FCSESTAT_BSY_MASK
#define FTFx_FCSESTAT_BSY_SHIFT                 FTFC_FCSESTAT_BSY_SHIFT
#define FTFx_FCSESTAT_BSY_WIDTH                 FTFC_FCSESTAT_BSY_WIDTH
#define FTFx_FCSESTAT_BSY(x)                    FTFC_FCSESTAT_BSY(x)
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
/* FERSTAT ECC错误状态寄存器位域定义 */
#define FTFx_FERSTAT_DFDIF_MASK                 FTFC_FERSTAT_DFDIF_MASK
#define FTFx_FERSTAT_DFDIF_SHIFT                FTFC_FERSTAT_DFDIF_SHIFT
#define FTFxFERSTAT_DFDIF_WIDTH                 FTFC_FERSTAT_DFDIF_WIDTH
#define FTFx_FERSTAT_DFDIF(x)                   FTFC_FERSTAT_DFDIF(x)
/* FERCNFG ECC错误配置寄存器位域定义 */
#define FTFx_FERCNFG_DFDIE_MASK                 FTFC_FERCNFG_DFDIE_MASK
#define FTFx_FERCNFG_DFDIE_SHIFT                FTFC_FERCNFG_DFDIE_SHIFT
#define FTFx_FERCNFG_DFDIE_WIDTH                FTFC_FERCNFG_DFDIE_WIDTH
#define FTFx_FERCNFG_DFDIE(x)                   FTFC_FERCNFG_DFDIE(x)
#define FTFx_FERCNFG_FDFD_MASK                  FTFC_FERCNFG_FDFD_MASK
#define FTFx_FERCNFG_FDFD_SHIFT                 FTFC_FERCNFG_FDFD_SHIFT
#define FTFx_FERCNFG_FDFD_WIDTH                 FTFC_FERCNFG_FDFD_WIDTH
#define FTFx_FERCNFG_FDFD(x)                    FTFC_FERCNFG_FDFD(x)
#endif

#else  /* ifndef FTFE */
#endif /* ifdef FTFE */

/* 清除 FSTAT 寄存器中的错误标志位（FPVIOL | ACCERR | RDCOLERR） */
#define CLEAR_FTFx_FSTAT_ERROR_BITS FTFx_FSTAT = (uint8_t)(FTFx_FSTAT_FPVIOL_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_RDCOLERR_MASK)

/* 半字大小：2 字节 */
#define FTFx_WORD_SIZE     0x0002U
/* 长字大小：4 字节 */
#define FTFx_LONGWORD_SIZE 0x0004U
/* 短语大小：8 字节 */
#define FTFx_PHRASE_SIZE   0x0008U
/* 双短语大小：16 字节 */
#define FTFx_DPHRASE_SIZE  0x0010U

/* FCCOB 偏移地址，用于存放资源代码 */
#if (FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE == FTFx_PHRASE_SIZE)
#define FTFx_RSRC_CODE_REG FTFx_FCCOB4
#else
#define FTFx_RSRC_CODE_REG FTFx_FCCOB8
#endif

/*******************************************************************************
 * Flash 硬件算法操作命令码
 * 这些命令码写入 FCCOB 寄存器以触发 Flash 控制器的特定操作
 *******************************************************************************/
#define FTFx_VERIFY_BLOCK             0x00U   /* 验证整块是否已擦除 */
#define FTFx_VERIFY_SECTION           0x01U   /* 验证指定区域是否已擦除 */
#define FTFx_PROGRAM_CHECK            0x02U   /* 检查编程结果 */
#define FTFx_READ_RESOURCE            0x03U   /* 读取特殊存储器资源 (IFR等) */
#define FTFx_PROGRAM_LONGWORD         0x06U   /* 编程长字 (4字节) */
#define FTFx_PROGRAM_PHRASE           0x07U   /* 编程短语 (8字节) */
#define FTFx_ERASE_BLOCK              0x08U   /* 擦除整个块 */
#define FTFx_ERASE_SECTOR             0x09U   /* 擦除扇区 */
#define FTFx_PROGRAM_SECTION          0x0BU   /* 编程段 (加速RAM写入) */
#define FTFx_VERIFY_ALL_BLOCK         0x40U   /* 验证所有块 */
#define FTFx_READ_ONCE                0x41U   /* 读取一次性编程区域 (IFR) */
#define FTFx_PROGRAM_ONCE             0x43U   /* 一次性编程 (IFR) */
#define FTFx_ERASE_ALL_BLOCK          0x44U   /* 擦除所有块 */
#define FTFx_SECURITY_BY_PASS         0x45U   /* 安全绕过 (解锁) */
#define FTFx_PFLASH_SWAP              0x46U   /* P-Flash 交换 */
#define FTFx_ERASE_ALL_BLOCK_UNSECURE 0x49U   /* 擦除所有块并解锁 */
#define FTFx_PROGRAM_PARTITION        0x80U   /* 分区编程 (FlexNVM) */
#define FTFx_SET_EERAM                0x81U   /* 设置 EERAM 功能 */


/*!
 * @name PFlash swap control codes — P-Flash 交换控制码
 * @{
 */
/*! @brief 初始化交换系统 */
#define FTFx_SWAP_SET_INDICATOR_ADDR 0x01U
/*! @brief 设置交换为更新状态 (Update) */
#define FTFx_SWAP_SET_IN_PREPARE     0x02U
/*! @brief 设置交换为完成状态 (Complete) */
#define FTFx_SWAP_SET_IN_COMPLETE    0x04U
/*! @brief 报告交换状态 */
#define FTFx_SWAP_REPORT_STATUS      0x08U
/*@}*/

/*!
 * @name PFlash swap states — P-Flash 交换状态
 * @{
 */
/*! @brief 未初始化交换模式 */
#define FTFx_SWAP_UNINIT        0x00U
/*! @brief 就绪交换模式 */
#define FTFx_SWAP_READY         0x01U
/*! @brief 更新交换模式 */
#define FTFx_SWAP_UPDATE        0x02U
/*! @brief 更新-已擦除交换模式 */
#define FTFx_SWAP_UPDATE_ERASED 0x03U
/*! @brief 完成交换模式 */
#define FTFx_SWAP_COMPLETE      0x04U
/*@}*/

/*! @brief FLASH_DRV_EraseResume 函数的等待计数 */
#define RESUME_WAIT_CNT         0x20U
/*! @brief FLASH_DRV_EraseSuspend 函数的等待计数 */
#define SUSPEND_WAIT_CNT        0x40U

/* 根据 Flash 类型选择 D-Flash IFR 读取资源地址 */
#if (FEATURE_FLS_IS_FTFE == 1U)
#define DFLASH_IFR_READRESOURCE_ADDRESS 0x8003F8U
#else /* FEATURE_FLASH_IS_FTFL == 1 or FEATURE_FLASH_IS_FTFA == 1 */
#define DFLASH_IFR_READRESOURCE_ADDRESS 0x8000FCU
#endif

/* 从32位值中提取各字节的宏 */
#define GET_BIT_0_7(value)   ((uint8_t)(((uint32_t)(value)) & 0xFFU))
#define GET_BIT_8_15(value)  ((uint8_t)((((uint32_t)(value)) >> 8) & 0xFFU))
#define GET_BIT_16_23(value) ((uint8_t)((((uint32_t)(value)) >> 16) & 0xFFU))
#define GET_BIT_24_31(value) ((uint8_t)(((uint32_t)(value)) >> 24))

/* Flash 安全状态掩码 */
#define FLASH_SECURITY_STATE_KEYEN     0x80U  /* 后门密钥使能标志 */
#define FLASH_SECURITY_STATE_UNSECURED 0x02U  /* 未安全锁定标志 */

/* CSEc 用户密钥大小代码最大值 */
#define CSE_KEY_SIZE_CODE_MAX 0x03U

/*!
 * @addtogroup flash_driver
 * @{
 */

/*!
 * @brief FlexRAM 功能控制码枚举
 *
 * 用于控制 FlexRAM 的工作模式：EEPROM 仿真、快速写入、RAM 模式等。
 * Implements : flash_flexRAM_function_control_code_t_Class
 */
typedef enum
{
    EEE_ENABLE                              = 0x00U,    /*!< FlexRAM 用于模拟 EEPROM */
    EEE_QUICK_WRITE                         = 0x55U,    /*!< FlexRAM 用于 EEPROM 快速写入 */
    EEE_STATUS_QUERY                        = 0x77U,    /*!< EEPROM 快速写入状态查询 */
    EEE_COMPLETE_INTERRUPT_QUICK_WRITE      = 0xAAU,    /*!< 完成被中断的 EEPROM 快速写入过程 */
    EEE_DISABLE                             = 0xFFU,    /*!< FlexRAM 用作传统 RAM */
} flash_flexRam_function_control_code_t;

/*!
 * @name Flash security status — Flash 安全状态返回值
 * @{
 */
/*! @brief Flash 当前处于非安全状态 */
#define FLASH_NOT_SECURE               0x01U
/*! @brief Flash 已安全锁定，后门密钥访问使能 */
#define FLASH_SECURE_BACKDOOR_ENABLED  0x02U
/*! @brief Flash 已安全锁定，后门密钥访问禁用 */
#define FLASH_SECURE_BACKDOOR_DISABLED 0x04U
/*@}*/

/*******************************************************************************
 * 回调函数周期
 *******************************************************************************/
#ifndef FLASH_CALLBACK_CS
/*! @brief FlashCheckSum 操作的回调周期计数
 *
 * 该值仅用于 FlashCheckSum 操作，过高频率的回调会影响性能。
 * 其他 Flash 操作在等待 Flash 控制器完成请求时会尽可能频繁地调用回调。
 */
#define FLASH_CALLBACK_CS 0x0AU
#endif

/*******************************************************************************
 * 空回调函数定义
 *******************************************************************************/
/*!
 * @name Null Callback function definition — 空回调函数定义
 * @{
 */
/*! @brief 空回调指针 */
#define NULL_CALLBACK      ((flash_callback_t)0xFFFFFFFFU)

#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
/*! @brief 空交换回调指针 */
#define NULL_SWAP_CALLBACK ((flash_swap_callback_t)0xFFFFFFFFU)
#endif
/*@}*/

/*******************************************************************************
 * 回调函数原型
 *******************************************************************************/
/*! @brief 回调函数指针类型
 *
 *   如果在应用程序中使用回调，从此函数可达的任何代码都不能放置在
 *   正在执行编程/擦除操作的 Flash 块中。
 *   可以使用 START/END_FUNCTION_DEFINITION/DECLARATION_RAMSECTION 宏
 *   将函数放置在 RAM 段中。
 */
typedef void (* flash_callback_t)(void);
#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
/*! @brief 交换回调函数指针类型 */
typedef bool (* flash_swap_callback_t)(uint8_t function);
#endif

/*******************************************************************************
 * Flash SSD 配置结构体
 *******************************************************************************/
/*!
 * @brief Flash 用户配置结构体
 *
 * 用户需要填写此结构体并将指针传递给 FLASH_DRV_Init 函数。
 * Implements : flash_user_config_t_Class
 */
typedef struct
{
    uint32_t PFlashBase;            /*!< P-Flash 存储器基地址 */
    uint32_t PFlashSize;            /*!< P-Flash 存储器大小（字节） */
    uint32_t DFlashBase;            /*!< 对于 FlexNVM 设备，这是 D-Flash (FlexNVM) 的基地址；
                                     *   对于非 FlexNVM 设备，此字段未使用 */
    uint32_t EERAMBase;             /*!< FlexRAM (FlexNVM 设备) 或加速 RAM (非 FlexNVM 设备) 的基地址 */
    flash_callback_t CallBack;      /*!< 回调函数，用于处理时间关键事件。从此函数可达的任何代码
                                     *   都不能放置在正在执行编程/擦除操作的 Flash 块中 */
} flash_user_config_t;

/*!
 * @brief Flash SSD 配置结构体
 *
 * 包含设备相关的 C90TFS/FTFx 静态参数。
 * PFlashBlockBase, PFlashBlockSize, DFlashBlockBase, EERAMBlockBase
 * 和 CallBack 通过 flash_user_config_t 传入。
 * DFlashBlockSize, EEESize 等其余参数由 FLASH_DRV_Init() 自动初始化。
 *
 * Implements : flash_ssd_config_t_Class
 */
typedef struct
{
    uint32_t PFlashBase;          /*!< P-Flash 存储器基地址 */
    uint32_t PFlashSize;          /*!< P-Flash 存储器大小（字节） */
    uint32_t DFlashBase;          /*!< 对于 FlexNVM 设备，这是 D-Flash (FlexNVM) 的基地址；
                                   *   对于非 FlexNVM 设备，此字段未使用 */
    uint32_t DFlashSize;          /*!< 对于 FlexNVM 设备，FlexNVM 中用作 D-Flash 的区域大小（字节）；
                                   *   对于非 FlexNVM 设备，此字段未使用 */
    uint32_t EERAMBase;           /*!< FlexRAM (FlexNVM 设备) 或加速 RAM (非 FlexNVM 设备) 的基地址 */
    uint32_t EEESize;             /*!< 对于 FlexNVM 设备，从 FlexRAM 分区的 EEPROM 区域大小（字节）；
                                   *   对于非 FlexNVM 设备，此字段未使用 */
    flash_callback_t CallBack;    /*!< 回调函数，用于处理时间关键事件。从此函数可达的任何代码
                                   *   都不能放置在正在执行编程/擦除操作的 Flash 块中 */
} flash_ssd_config_t;

/*!
 * @brief EEPROM 状态结构体
 *
 * Implements : flash_eeprom_status_t_Class
 */
typedef struct
{
    uint8_t brownOutCode;               /*!< 掉电检测代码 */
    uint16_t numOfRecordReqMaintain;    /*!< 需要维护的 EEPROM 快速写入记录数 */
    uint16_t sectorEraseCount;          /*!< EEPROM 扇区擦除计数 */
} flash_eeprom_status_t;

/*******************************************************************************
 * Flash SSD 函数原型
 *******************************************************************************/
/*!
 * @name Flash driver APIs — Flash 驱动 API
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @brief 初始化 Flash 模块
 *
 * 通过 SSD 配置结构体报告存储器配置信息来初始化 Flash 模块。
 *
 * @param[in] pUserConf 用户配置结构体指针
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @return 操作状态
 *        - STATUS_SUCCESS:    操作成功
 */
status_t FLASH_DRV_Init(const flash_user_config_t * const pUserConf,
                        flash_ssd_config_t * const pSSDConfig);

/*!
 * @brief 获取 P-Flash 保护状态
 *
 * 读取当前 P-Flash 保护寄存器的值。
 * 由于获取保护状态的时间消耗极低，无需使用回调函数支持时间关键事件。
 *
 * @param[out] protectStatus 返回 P-Flash 保护的当前值。
 *                          每一位对应总 P-Flash 的 1/32 区域的保护状态。
 *                          最低位对应 P-Flash 最低地址区域，最高位对应最高地址区域。
 *                          取值含义：
 *                          - 0：该区域受保护
 *                          - 1：该区域未保护
 */
void FLASH_DRV_GetPFlashProtection(uint32_t * protectStatus);

/*!
 * @brief 设置 P-Flash 保护
 *
 * 将 P-Flash 保护设置为期望的状态。设置保护受限于保护转换限制。
 * 如果存在设置冲突，将返回错误码，当前保护状态不会改变。
 *
 * @param[in] protectStatus 期望设置的 P-Flash 保护状态值。
 *                          每一位对应总 P-Flash 的 1/32 区域的保护状态。
 *                          最低位对应最低地址区域，最高位对应最高地址区域。
 *                          取值含义：
 *                          - 0：该区域受保护
 *                          - 1：该区域未保护
 * @return 操作状态
 *        - STATUS_SUCCESS:  操作成功
 *        - STATUS_ERROR:    操作失败
 */
status_t FLASH_DRV_SetPFlashProtection(uint32_t protectStatus);

/*!
 * @brief 获取 Flash 安全状态
 *
 * 读取当前 Flash 安全状态，包括安全使能状态和后门密钥使能状态。
 *
 * @param[out] securityState 返回当前安全状态码
 *                          - FLASH_NOT_SECURE (0x01U): Flash 当前非安全状态
 *                          - FLASH_SECURE_BACKDOOR_ENABLED (0x02U): Flash 已安全锁定，
 *                            后门密钥访问使能
 *                          - FLASH_SECURE_BACKDOOR_DISABLED (0x04U): Flash 已安全锁定，
 *                            后门密钥访问禁用
 */
void FLASH_DRV_GetSecurityState(uint8_t * securityState);

/*!
 * @brief Flash 安全绕过（解锁）
 *
 * 通过比较用户提供的后门密钥与 Flash 配置区中的密钥来解锁设备。
 * 如果匹配，则释放安全锁定；否则返回错误码。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] keyBuffer 包含后门密钥的用户缓冲区指针
 * @return 操作状态
 *        - STATUS_SUCCESS:  操作成功
 *        - STATUS_ERROR:    操作失败
 *        - STATUS_BUSY:     操作忙
 */
status_t FLASH_DRV_SecurityBypass(const flash_ssd_config_t * pSSDConfig,
                                  const uint8_t * keyBuffer);

/*!
 * @brief 擦除所有 Flash 块
 *
 * 擦除所有 Flash 存储器，初始化 FlexRAM，验证所有存储器内容，然后释放 MCU 安全锁定。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @return 操作状态
 *        - STATUS_SUCCESS:   操作成功
 *        - STATUS_ERROR:     操作失败
 *        - STATUS_BUSY:      操作忙
 */

status_t FLASH_DRV_EraseAllBlock(const flash_ssd_config_t * pSSDConfig);

/*!
 * @brief 验证所有 Flash 块
 *
 * 检查 P-Flash 和/或 D-Flash、EEPROM 备份区域以及 D-Flash IFR 是否已擦除到
 * 指定的读取裕量等级。如果验证通过，则释放安全锁定。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] marginLevel 读取裕量选择：
 *                        - marginLevel = 0x0U: 使用正常读取等级
 *                        - marginLevel = 0x1U: 使用用户读取等级
 *                        - marginLevel = 0x2U: 使用工厂读取等级
 * @return 操作状态
 *        - STATUS_SUCCESS:   操作成功
 *        - STATUS_ERROR:     操作失败
 *        - STATUS_BUSY:      操作忙
 */
status_t FLASH_DRV_VerifyAllBlock(const flash_ssd_config_t * pSSDConfig,
                                  uint8_t marginLevel);

/*!
 * @brief 擦除 Flash 扇区
 *
 * 擦除 P-Flash 或 D-Flash 存储器中的一个或多个扇区。
 * 如果用户提供的 size 为零，则无论输入验证如何，始终返回 STATUS_SUCCESS。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 待擦除的第一个扇区中的地址。
 *            用户需要确保该地址位于 P-FLASH 或 D-FLASH 块中。
 *            地址对齐要求如下表所示：
 *           |    Flash 类型/MCU  | S32K116 | S32K118 | S32K142 | S32K144 | S32K146 | S32K148 |
 *           |:------------------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
 *           |       P-FLASH      |    8    |    8    |    8    |    16   |    16   |    16   |
 *           |       D-FLASH      |    8    |    8    |    8    |    8    |    8    |    16   |
 *
 * @param[in] size 要擦除的大小（字节），用于确定要擦除的扇区数量。
 *            对齐要求同上表。
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_EraseSector(const flash_ssd_config_t * pSSDConfig,
                               uint32_t dest,
                               uint32_t size);

/*!
 * @brief 验证 Flash 区域
 *
 * 检查 P-Flash 或 D-Flash 存储器的指定区域是否已擦除到指定的读取裕量等级。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 待验证操作的起始地址。
 *            用户需要确保该地址位于 P-FLASH 或 D-FLASH 块中。
 *            对齐要求如下表所示：
 *           |    Flash 类型/MCU  | S32K116 | S32K118 | S32K142 | S32K144 | S32K146 | S32K148 |
 *           |:------------------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
 *           |       P-FLASH      |    8    |    8    |    8    |    16   |    16   |    16   |
 *           |       D-FLASH      |    8    |    8    |    8    |    8    |    8    |    16   |
 *
 * @param[in] number 要验证的对齐单元数量。请参考相关参考手册获取正确的对齐约束信息。
 * @param[in] marginLevel 读取裕量选择：
 *                        - marginLevel = 0x0U: 使用正常读取等级
 *                        - marginLevel = 0x1U: 使用用户读取等级
 *                        - marginLevel = 0x2U: 使用工厂读取等级
 * @return 操作状态
 *        - STATUS_SUCCESS:   操作成功
 *        - STATUS_ERROR:     操作失败
 *        - STATUS_BUSY:      操作忙
 */
status_t FLASH_DRV_VerifySection(const flash_ssd_config_t * pSSDConfig,
                                 uint32_t dest,
                                 uint16_t number,
                                 uint8_t marginLevel);

/*!
 * @brief 擦除挂起
 *
 * 用于挂起当前正在执行的 Flash 擦除扇区命令。
 * 此函数必须位于 RAM 存储器或不同 Flash 块中（非目标块），以避免 RWW (Read-While-Write) 错误。
 */
void FLASH_DRV_EraseSuspend(void);

/*!
 * @brief 擦除恢复
 *
 * 用于恢复之前挂起的 Flash 擦除扇区命令。
 * 此函数必须位于 RAM 存储器或不同 Flash 块中（非目标块），以避免 RWW 错误。
 */
void FLASH_DRV_EraseResume(void);

/*!
 * @brief 一次性读取 (Read Once)
 *
 * 根据给定的记录编号，读取位于 P-Flash IFR 中的保留 64 字节字段。
 * 请参阅相应参考手册获取正确的记录编号值。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] recordIndex 要读取的记录索引，范围 0x0U 到 0x7U 或 0x0U 到 0xF
 *                        具体取决于芯片型号。
 * @param[in] pDataArray 用于返回读取一次命令数据的指针
 * @return 操作状态
 *        - STATUS_SUCCESS:   操作成功
 *        - STATUS_ERROR:     操作失败
 *        - STATUS_BUSY:      操作忙
 */
status_t FLASH_DRV_ReadOnce(const flash_ssd_config_t * pSSDConfig,
                            uint8_t recordIndex,
                            uint8_t * pDataArray);

/*!
 * @brief 一次性编程 (Program Once)
 *
 * 根据给定的记录编号，编程位于 P-Flash IFR 中的保留 64 字节字段。
 * 请参阅相应参考手册获取正确的记录编号值。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] recordIndex 要编程的记录索引，范围 0x0U 到 0x7U 或 0x0U 到 0xF
 *                        具体取决于芯片型号。
 * @param[in] pDataArray 包含要编程数据的缓冲区指针
 * @return 操作状态
 *        - STATUS_SUCCESS:   操作成功
 *        - STATUS_ERROR:     操作失败
 *        - STATUS_BUSY:      操作忙
 */
status_t FLASH_DRV_ProgramOnce(const flash_ssd_config_t * pSSDConfig,
                               uint8_t recordIndex,
                               const uint8_t * pDataArray);

#if FEATURE_FLS_HAS_READ_RESOURCE_CMD
/*!
 * @brief 读取资源 (Read Resource)
 *
 * 从 Flash 存储器模块中的特殊用途存储器读取数据，
 * 包括 P-Flash IFR、Swap IFR、D-Flash IFR 空间和版本 ID。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 读取操作的起始地址，需 8 字节对齐
 * @param[out] pDataArray 读取资源命令返回的数据指针
 * @param[in] resourceSelectCode 资源选择码：
 *                               - 0: Flash IFR
 *                               - 1: 版本 ID
 * @return 操作状态
 *        - STATUS_SUCCESS:   操作成功
 *        - STATUS_ERROR:     操作失败
 *        - STATUS_BUSY:      操作忙
 */
status_t FLASH_DRV_ReadResource(const flash_ssd_config_t * pSSDConfig,
                                uint32_t dest,
                                uint8_t * pDataArray,
                                uint8_t resourceSelectCode);
#endif

/*!
 * @brief Flash 编程
 *
 * 在 P-Flash 或 D-Flash 块上连续编程 4 字节（长字命令）或 8 字节（短语命令）。
 * 如果用户提供的 size 为零，则无论输入验证如何，始终返回 STATUS_SUCCESS。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 编程操作的起始地址，需 8 字节对齐
 * @param[in] size 要编程的大小（字节），需 8 字节对齐
 * @param[in] pData 源数据指针，用于编程操作
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_Program(const flash_ssd_config_t * pSSDConfig,
                           uint32_t dest,
                           uint32_t size,
                           const uint8_t * pData);

/*!
 * @brief Flash 编程检查
 *
 * 测试先前编程的 P-Flash 或 D-Flash 长字在指定裕量等级下是否正确读取。
 * 如果用户提供的 size 为零，则无论输入验证如何，始终返回 STATUS_SUCCESS。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 编程检查操作的起始地址，需 4 字节对齐
 * @param[in] size 检查的大小（字节），需 4 字节对齐
 * @param[in] pExpectedData 期望数据的指针
 * @param[in] pFailAddr 返回第一个对齐失败的地址
 * @param[in] marginLevel 读取裕量选择：
 *                        - marginLevel = 0x1U: 在用户裕量 1/0 等级读取
 *                        - marginLevel = 0x2U: 在工厂裕量 1/0 等级读取
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_ProgramCheck(const flash_ssd_config_t * pSSDConfig,
                                uint32_t dest,
                                uint32_t size,
                                const uint8_t * pExpectedData,
                                uint32_t * pFailAddr,
                                uint8_t marginLevel);

/*!
 * @brief 计算校验和
 *
 * 对指定的 Flash 存储器范围内的每个字节数据进行 32 位无进位累加求和，
 * 提供快速的数据完整性检查方法。
 * 此 API 的回调时间周期由 flash_driver.h 中的 FLASH_CALLBACK_CS 宏确定，
 * 该宏用作此 API 中 CallBack() 函数调用的计数值。
 * 用户可根据需求更改此值以获得最大允许的回调时间周期。
 * 如果用户提供的 size 为零，则无论输入验证如何，始终返回 STATUS_SUCCESS。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 要求和计算的 Flash 范围起始地址
 * @param[in] size 要求和计算的 Flash 范围大小（字节）
 * @param[in] pSum 返回累加和值的指针
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 */
status_t FLASH_DRV_CheckSum(const flash_ssd_config_t * pSSDConfig,
                            uint32_t dest,
                            uint32_t size,
                            uint32_t * pSum);

#if FEATURE_FLS_HAS_PROGRAM_SECTION_CMD
/*!
 * @brief Flash 段编程 (Program Section)
 *
 * 将段编程缓冲区中的数据编程到 Flash 存储器中先前已擦除的位置。
 * 数据通过写入加速 RAM 和设置为 RAM 模式的 FlexRAM 预加载到段编程缓冲区。
 * 段编程缓冲区的大小限制为 FlexRAM 除以某个比率的值。
 * 请参考相关参考手册获取正确的比率值。
 *
 * 对于包含交换功能的芯片，如果在 FlashProgramSection 期间遇到交换指示器地址，
 * 将绕过而不设置 FPVIOL，但内容不会被编程。
 * 此外，用于编程交换指示器的源数据内容将在命令完成后重新初始化为 0xFF。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 编程操作的起始地址。
 *            用户需要确保该地址位于 P-FLASH 或 D-FLASH 块中。
 *            对齐要求如下表所示：
 *           |    Flash 类型/MCU  | S32K116 | S32K118 | S32K142 | S32K144 | S32K146 | S32K148 |
 *           |:------------------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
 *           |       P-FLASH      |    8    |    8    |    8    |    16   |    16   |    16   |
 *           |       D-FLASH      |    8    |    8    |    8    |    8    |    8    |    16   |
 *
 * @param[in] number 要编程的对齐单元数量。请参考相关参考手册获取正确的对齐约束值。
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_UNSUPPORTED:     操作不支持
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_ProgramSection(const flash_ssd_config_t * pSSDConfig,
                                  uint32_t dest,
                                  uint16_t number);
#endif

#if FEATURE_FLS_HAS_ERASE_BLOCK_CMD
/*!
 * @brief 擦除 Flash 块
 *
 * 擦除单个 P-Flash 或 D-Flash 块中的所有地址。
 * 对于包含多个逻辑 P-Flash 或 D-Flash 块的芯片，此 API 单次调用擦除单个块。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 擦除操作的起始地址。
 *            用户需要确保该地址位于 P-FLASH 或 D-FLASH 块中。
 *            对齐要求如下表所示：
 *           |    Flash 类型/MCU  | S32K116 | S32K118 | S32K142 | S32K144 | S32K146 | S32K148 |
 *           |:------------------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
 *           |       P-FLASH      |    8    |    8    |    8    |    16   |    16   |    16   |
 *           |       D-FLASH      |    8    |    8    |    8    |    8    |    8    |    16   |
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_EraseBlock(const flash_ssd_config_t * pSSDConfig,
                              uint32_t dest);
#endif

#if FEATURE_FLS_HAS_READ_1S_BLOCK_CMD
/*!
 * @brief 验证 Flash 块
 *
 * 检查整个 P-Flash 或 D-Flash 块是否已擦除到指定的裕量等级。
 * 对于包含多个逻辑 P-Flash 或 D-Flash 块的芯片，此 API 单次调用擦除单个块。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 验证操作的起始地址。
 *            用户需要确保该地址位于 P-FLASH 或 D-FLASH 块中。
 *            对齐要求如下表所示：
 *           |    Flash 类型/MCU  | S32K116 | S32K118 | S32K142 | S32K144 | S32K146 | S32K148 |
 *           |:------------------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
 *           |       P-FLASH      |    8    |    8    |    8    |    16   |    16   |    16   |
 *           |       D-FLASH      |    8    |    8    |    8    |    8    |    8    |    16   |
 * @param[in] marginLevel 读取裕量选择：
 *                        - marginLevel = 0x0U: 使用正常读取等级
 *                        - marginLevel = 0x1U: 使用用户读取等级
 *                        - marginLevel = 0x2U: 使用工厂读取等级
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_VerifyBlock(const flash_ssd_config_t * pSSDConfig,
                               uint32_t dest,
                               uint8_t marginLevel);
#endif

#if FEATURE_FLS_HAS_FLEX_NVM
/*!
 * @brief 获取 EERAM 保护
 *
 * 读取 FlexRAM 中哪些 EEPROM 部分受到保护，防止编程和擦除操作。
 * 由于获取保护状态的时间消耗极低，无需使用回调函数支持时间关键事件。
 *
 * @param[out] protectStatus 返回 EEPROM 保护寄存器的当前值。
 *                          每一位对应总 EEPROM 使用区域的 1/8 的保护状态。
 *                          最低位对应 EEPROM 最低地址区域，最高位对应最高地址区域。
 *                          取值含义：
 *                          - 0：该区域受保护
 *                          - 1：该区域未保护
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_UNSUPPORTED:     操作不支持
 */
status_t FLASH_DRV_GetEERAMProtection(uint8_t * protectStatus);

/*!
 * @brief 设置 EERAM 保护
 *
 * 为 FlexRam 的 EEPROM 使用区域设置期望的保护状态。
 * 设置保护受限于保护转换限制。如果存在设置冲突，将返回失败信息，
 * 当前保护状态不会改变。
 *
 * @param[in] protectStatus 要写入 EEPROM 保护寄存器的期望保护状态值。
 *                          每一位对应总 EEPROM 使用区域的 1/8 的保护状态。
 *                          最低位对应 EEPROM 最低地址区域，最高位对应最高地址区域。
 *                          取值含义：
 *                          - 0：该区域受保护
 *                          - 1：该区域未保护
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_UNSUPPORTED:     操作不支持
 */
status_t FLASH_DRV_SetEERAMProtection(uint8_t protectStatus);

/*!
 * @brief 设置 FlexRAM 功能
 *
 * 更改 FlexRAM 的功能。当未分区用于 EEPROM 仿真时，FlexRAM 通常用作传统 RAM。
 * 否则，FlexRAM 通常用于存储 EEPROM 数据，写入 EEPROM 可以是正常写入或快速写入。
 *
 * 此外，此函数可用于获取 EEPROM 状态或完成被中断的 EEPROM 快速写入过程。
 * 例如，在分区后获得 EEPROM 备份后，FlexRAM 相应地用于 EEPROM 使用。
 * 如果想将 FlexRAM 更改为传统 RAM 以便用于 FlashProgramSection()，请使用
 * 功能控制码 0xFFU 调用此 API。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] flexRamFuncCode FlexRam 功能控制码：
 *                            - 0x00U: FlexRAM 用于模拟 EEPROM
 *                            - 0x55U: FlexRAM 用于 EEPROM 快速写入
 *                            - 0x77U: EEPROM 快速写入状态查询
 *                            - 0xAAU: 完成被中断的 EEPROM 快速写入过程
 *                            - 0xFFU: FlexRAM 用作普通 RAM
 * @param[in] byteOfQuickWrite 分配给 EEPROM 快速写入的 FlexRAM 字节数。
 *                              仅用于 EEE_QUICK_WRITE 命令。
 *                              不能小于 16 字节且不能超过 512 字节，
 *                              在 EEPROM 快速写入中必须被 4 整除。
 *                              如果不用于 EEPROM 快速写入，应为 0。
 * @param[out] pEEPROMStatus EEPROM 状态指针。仅用于 EEE_STATUS_QUERY 命令，
 *                            如果不用于 EEPROM 状态查询，应为 NULL。
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_SetFlexRamFunction(const flash_ssd_config_t * pSSDConfig,
                                      flash_flexRam_function_control_code_t flexRamFuncCode,
                                      uint16_t byteOfQuickWrite,
                                      flash_eeprom_status_t * const pEEPROMStatus);

/*!
 * @brief EEPROM 仿真写入
 *
 * 将数据写入已分区为 EEPROM 使用的 FlexRAM 区域以进行 EEPROM 操作。
 * 数据写入 FlexRAM 的 EEPROM 使用区域后，EEPROM 文件系统将以轮转方式
 * 在 FlexNVM 的 EEPROM 备份区域中创建新的数据记录。
 *
 * 对用户提供的目标和大小参数没有对齐约束。根据用户输入，此 API 按以下规则
 * 设置写入优先级：
 * 如果目标是 32 位对齐且大小不小于 32 位，则调用 32 位写入。
 * 如果目标是 16 位对齐且大小不小于 16 位，则调用 16 位写入。
 * 如果目标是 8 位对齐且大小不小于 8 位，则调用 8 位写入。
 * 当 EEPROM 设置为 EEPROM 快速写入模式时，目标地址需 4 字节对齐，大小需被 4 整除。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] dest 写入操作的起始地址
 * @param[in] size 要写入的大小（字节）
 * @param[in] pData 源数据指针，用于写入操作
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 */
status_t FLASH_DRV_EEEWrite(const flash_ssd_config_t * pSSDConfig,
                            uint32_t dest,
                            uint32_t size,
                            const uint8_t * pData);

/*!
 * @brief Flash D/E-Flash 分区 (Partition)
 *
 * 准备 FlexNVM 块以用作 D-Flash、EEPROM 备份或两者的组合，并初始化 FlexRAM。
 * 此外，如果启用了 CSEc，此函数还用于配置用户密钥数量和密钥"仅验证"属性。
 *
 * 应在应用程序的整个生命周期内使用单一分区选择，以保证 Flash 模块的擦写耐久性和数据保持能力。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] uEEEDataSizeCode EEPROM 数据大小代码
 * @param[in] uDEPartitionCode FlexNVM 分区代码
 * @param[in] uCSEcKeySize CSEc 密钥大小代码，如果不用于配置 CSEc 部分，应为 0。
 *             取值：
 *             - 0x00U: 用户密钥数量为零
 *                      从总 4K EEERAM 空间中减去的字节数为 0
 *             - 0x01U: 用户密钥数为 1 到 6 个
 *                      从总 4K EEERAM 空间中减去的字节数为 128 字节
 *             - 0x02U: 用户密钥数为 1 到 12 个
 *                      从总 4K EEERAM 空间中减去的字节数为 256 字节
 *             - 0x03U: 用户密钥数为 1 到 24 个
 *                      从总 4K EEERAM 空间中减去的字节数为 512 字节
 * @param[in] uSFE 安全标志扩展，如果不用于配置 CSEc 部分，应为 false
 * @param[in] flexRamEnableLoadEEEData FlexRAM 复位期间加载选项
 *            - true : 复位序列期间 FlexRAM 加载有效的 EEPROM 数据
 *            - false : 复位序列期间 FlexRAM 不加载数据
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_DEFlashPartition(const flash_ssd_config_t * pSSDConfig,
                                    uint8_t uEEEDataSizeCode,
                                    uint8_t uDEPartitionCode,
                                    uint8_t uCSEcKeySize,
                                    bool uSFE,
                                    bool flexRamEnableLoadEEEData);

/*!
 * @brief 获取 D-Flash 保护
 *
 * 读取当前 D-Flash 保护状态。由于获取保护状态的时间消耗极低，
 * 无需使用回调函数支持时间关键事件。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[out] protectStatus 返回 D-Flash 保护寄存器的当前值。
 *                          每一位对应总 D-Flash 的 1/8 的保护状态。
 *                          最低位对应 D-Flash 最低地址区域，最高位对应最高地址区域。
 *                          取值含义：
 *                          - 0：该区域受保护
 *                          - 1：该区域未保护
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_UNSUPPORTED:     操作不支持
 */
status_t FLASH_DRV_GetDFlashProtection(const flash_ssd_config_t * pSSDConfig,
                                       uint8_t * protectStatus);

/*!
 * @brief 设置 D-Flash 保护
 *
 * 设置 D-Flash 保护到期望的状态。设置保护受限于保护转换限制。
 * 如果存在设置冲突，将返回失败信息，当前保护状态不会改变。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] protectStatus 要写入 D-Flash 保护寄存器的期望保护状态值。
 *                          每一位对应总 D-Flash 的 1/8 的保护状态。
 *                          最低位对应 D-Flash 最低地址区域，最高位对应最高地址区域。
 *                          取值含义：
 *                          - 0：该区域受保护
 *                          - 1：该区域未保护
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_UNSUPPORTED:     操作不支持
 */
status_t FLASH_DRV_SetDFlashProtection(const flash_ssd_config_t * pSSDConfig,
                                       uint8_t protectStatus);
#endif /* End of FEATURE_FLS_HAS_FLEX_NVM */

#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
/*!
 * @brief P-Flash 块交换
 *
 * 交换内存映射中总逻辑 P-Flash 存储器块的两个半区。
 *
 * 通过 pSwapCallBack() 参数，让用户代码了解交换过程每个阶段的交换状态，
 * 从而使用户能够干预交换进度。
 * 要在每个中间交换状态停止，请将此回调函数的返回值设置为 FALSE。
 * 要在单次调用内完成交换过程，请将此函数的返回值设置为 TRUE。
 *
 * 当交换系统处于 UPDATE 状态时，在应用程序代码或交换回调函数中
 * 擦除非活动交换指示器。
 *
 * 此外，如果用户不想使用交换回调参数，请传递 NULL_SWAP_CALLBACK 作为空指针。
 * 在这种情况下，PFlashSwap() 的行为与将 pSwapCallBack 返回值设置为 TRUE 相同，
 * 并且当交换系统处于 UPDATE 状态时，用户无需擦除非活动交换指示器。
 *
 * 交换指示器必须位于 P-Flash 块的下半区，但不能在 Flash 配置区域内。
 * 如果 P-Flash 块有两个逻辑块，交换指示器必须在 P-Flash 块 0 中。
 * 如果 P-Flash 块有四个逻辑块，交换指示器可以在块 0 或块 1 中。
 * 不能在 Flash 配置字段中。
 *
 * 一旦交换系统初始化后，用户必须为所有交换控制码使用相同的交换指示器，
 * 但报告交换状态除外。要将交换系统刷新为未初始化状态，
 * 请使用 FlashEraseAllBlock() 清理交换环境。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] addr 交换指示器的地址
 * @param[in] pSwapCallback 交换过程中执行特定任务的回调函数
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 */
status_t FLASH_DRV_PFlashSwap(const flash_ssd_config_t * pSSDConfig,
                              uint32_t addr,
                              flash_swap_callback_t pSwapCallback);

/*!
 * @brief 执行交换控制命令
 *
 * 根据交换命令参数提供的交换控制码执行相应的交换控制操作。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @param[in] addr 交换指示器的地址
 * @param[in] swapcmd 交换控制码：
 *                    - 0x01U: 初始化交换系统
 *                    - 0x02U: 设置交换为更新状态
 *                    - 0x04U: 设置交换为完成状态
 *                    - 0x08U: 报告交换状态
 * @param[in] pCurrentSwapMode 当前交换模式：
 *                             - 0x00U: 未初始化
 *                             - 0x01U: 就绪
 *                             - 0x02U: 更新
 *                             - 0x03U: 更新-已擦除
 *                             - 0x04U: 完成
 * @param[in] pCurrentSwapBlockStatus 当前交换块状态，指示当前哪个程序 Flash 块
 *                                    位于相对 Flash 地址 0x0_0000
 *                                    - 0x00U: 程序 Flash 块 0
 *                                    - 0x01U: 程序 Flash 块 1
 * @param[in] pNextSwapBlockStatus 下一个交换块状态，指示下次复位后哪个程序 Flash 块
 *                                 位于相对 Flash 地址 0x0_0000
 *                                 - 0x00U: 程序 Flash 块 0
 *                                 - 0x01U: 程序 Flash 块 1
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_PFlashSwapCtl(const flash_ssd_config_t * pSSDConfig,
                                 uint32_t addr,
                                 uint8_t swapcmd,
                                 uint8_t * pCurrentSwapMode,
                                 uint8_t * pCurrentSwapBlockStatus,
                                 uint8_t * pNextSwapBlockStatus);

#endif /* End of FEATURE_FLS_HAS_PF_BLOCK_SWAP */

#if FEATURE_FLS_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD
/*!
 * @brief 擦除所有 Flash 块并解锁
 *
 * 擦除所有 Flash 存储器，初始化 FlexRAM，验证所有存储器内容，然后释放 MCU 安全锁定。
 *
 * @param[in] pSSDConfig SSD 配置结构体指针
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 *        - STATUS_ERROR:           操作失败
 *        - STATUS_BUSY:            操作忙
 */
status_t FLASH_DRV_EraseAllBlockUnsecure(const flash_ssd_config_t * pSSDConfig);
#endif /* End of FEATURE_FLS_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD */

/*!
 * @brief 使能命令完成中断
 *
 * 使能 FTFC 命令完成时产生中断。
 *
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 */
status_t FLASH_DRV_EnableCmdCompleteInterupt(void);

/*!
 * @brief 禁用命令完成中断
 *
 */
void FLASH_DRV_DisableCmdCompleteInterupt(void);

/*!
 * @brief 检查命令完成标志
 *
 * @return 命令完成标志
 *        - true: FTFC 命令已完成
 *        - false: FTFC 命令正在执行中
 *
 * Implements    : FLASH_DRV_GetCmdCompleteFlag_Activity
 */
static inline bool FLASH_DRV_GetCmdCompleteFlag(void)
{
    return (((FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK) >> FTFx_FSTAT_CCIF_SHIFT) != 0U);
}

/*!
 * @brief 使能读取冲突错误中断
 *
 * 使能在 FTFC 读取冲突错误发生时产生中断。
 *
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 */
status_t FLASH_DRV_EnableReadColisionInterupt(void);

/*!
 * @brief 禁用读取冲突错误中断
 *
 */
void FLASH_DRV_DisableReadColisionInterupt(void);

/*!
 * @brief 检查读取冲突错误标志
 *
 * @return 读取冲突错误标志
 *        - true: 检测到冲突错误
 *        - false: 未检测到冲突错误
 *
 * Implements    : FLASH_DRV_GetReadColisionFlag_Activity
 */
static inline bool FLASH_DRV_GetReadColisionFlag(void)
{
    return (((FTFx_FSTAT & FTFx_FSTAT_RDCOLERR_MASK) >> FTFx_FSTAT_RDCOLERR_SHIFT) != 0U);
}

/*!
 * @brief 清除读取冲突错误标志
 *
 * Implements    : FLASH_DRV_ClearReadColisionFlag_Activity
 */
static inline void FLASH_DRV_ClearReadColisionFlag(void)
{
    FTFx_FSTAT = FTFx_FSTAT_RDCOLERR_MASK;
}

#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
/*!
 * @brief 使能双位错误检测中断
 *
 * 使能在平台 Flash 控制器有效读取访问期间检测到不可纠正的 ECC 错误时
 * 产生双位错误检测中断。
 *
 * @return 操作状态
 *        - STATUS_SUCCESS:         操作成功
 */
status_t FLASH_DRV_EnableDoubleBitFaultInterupt(void);

/*!
 * @brief 禁用双位错误检测中断
 *
 */
void FLASH_DRV_DisableDoubleBitFaultInterupt(void);

/*!
 * @brief 检查双位错误标志
 *
 * @return Flash 错误状态
 *        - true: 检测到双位错误
 *        - false: 未检测到双位错误
 *
 * Implements    : FLASH_DRV_GetDoubleBitFaultFlag_Activity
 */
static inline bool FLASH_DRV_GetDoubleBitFaultFlag(void)
{
    return (((FTFx_FERSTAT & FTFx_FERSTAT_DFDIF_MASK) >> FTFx_FERSTAT_DFDIF_SHIFT) != 0U);
}

/*!
 * @brief 清除双位错误检测标志
 *
 * Implements    : FLASH_DRV_ClearDoubleBitFaultFlag_Activity
 */
static inline void FLASH_DRV_ClearDoubleBitFaultFlag(void)
{
    FTFx_FERSTAT = FTFx_FERSTAT_DFDIF_MASK;
}

/*!
 * @brief 强制双位错误检测
 *
 * 允许用户模拟设置双位错误检测中断标志，以检查相关的中断服务程序。
 *
 * @param[in] isEnable 使能/禁用模拟双位错误检测标志
 *
 * Implements    : FLASH_DRV_ForceDoubleBitFaultDetectCmd_Activity
 */
static inline void FLASH_DRV_ForceDoubleBitFaultDetectCmd(bool isEnable)
{
    if (true == isEnable)
    {
        FTFx_FERCNFG |= FTFx_FERCNFG_FDFD_MASK;
    }
    else
    {
        FTFx_FERCNFG &= (uint8_t)(~FTFx_FERCNFG_FDFD_MASK);
    }
}
#endif /* End of FEATURE_FLS_HAS_DETECT_ECC_ERROR */

/*!
 * @brief 获取默认 Flash 配置
 *
 * 获取默认的 Flash 用户配置。
 *
 * @param[out] config Flash 用户配置结构体指针
 */
void FLASH_DRV_GetDefaultConfig(flash_user_config_t * const config);

#if defined(__cplusplus)
}
#endif

/*@}*/ /* End of Flash driver APIs*/
/*! @}*/ /* End of addtogroup flash_driver */

#endif /* FLASH_DRIVER_H */
