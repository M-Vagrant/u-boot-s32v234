/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 *
 * U-Boot Implementation for the Freescale SAC58R Functional Validation Board
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux-sac58r.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/clock.h>
#include <mmc.h>
#include <fsl_esdhc.h>
#include <miiphy.h>
#include <netdev.h>
#include <i2c.h>
#include <asm/arch/dmachmux-sac58r.h>

#include "sac58rfvb_int_routing.h"

DECLARE_GLOBAL_DATA_PTR;

void setup_iomux_ddr(void)
{
	static const iomux_v3_cfg_t ddr_pads[] = {
		SAC58R_PAD_DDR_A15__DDR_A15,		
		SAC58R_PAD_DDR_A14__DDR_A14,		
		SAC58R_PAD_DDR_A13__DDR_A13,		
		SAC58R_PAD_DDR_A12__DDR_A12,		
		SAC58R_PAD_DDR_A11__DDR_A11,		
		SAC58R_PAD_DDR_A10__DDR_A10,		
		SAC58R_PAD_DDR_A9__DDR_A9,		
		SAC58R_PAD_DDR_A8__DDR_A8,		
		SAC58R_PAD_DDR_A7__DDR_A7,		
		SAC58R_PAD_DDR_A6__DDR_A6,		
		SAC58R_PAD_DDR_A5__DDR_A5,		
		SAC58R_PAD_DDR_A4__DDR_A4,		
		SAC58R_PAD_DDR_A3__DDR_A3,		
		SAC58R_PAD_DDR_A2__DDR_A2,		
		SAC58R_PAD_DDR_A1__DDR_A1,		
		SAC58R_PAD_DDR_A0__DDR_A0,		
		SAC58R_PAD_DDR_BA2__DDR_BA_2,	
		SAC58R_PAD_DDR_BA1__DDR_BA_1,	
		SAC58R_PAD_DDR_BA0__DDR_BA_0,	
		SAC58R_PAD_DDR_CAS__DDR_CAS,		
		SAC58R_PAD_DDR_CKE1__DDR_CKE1,	
		SAC58R_PAD_DDR_CKE0__DDR_CKE0,	
		SAC58R_PAD_DDR_CLK0__DDR_CLK0,	
		SAC58R_PAD_DDR_CS_B1__DDR_CS_B1,	
		SAC58R_PAD_DDR_CS_B0__DDR_CS_B0,
		SAC58R_PAD_DDR_D31__DDR_D31,		
		SAC58R_PAD_DDR_D30__DDR_D30,		
		SAC58R_PAD_DDR_D29__DDR_D29,		
		SAC58R_PAD_DDR_D28__DDR_D28,		
		SAC58R_PAD_DDR_D27__DDR_D27,		
		SAC58R_PAD_DDR_D26__DDR_D26,		
		SAC58R_PAD_DDR_D25__DDR_D25,		
		SAC58R_PAD_DDR_D24__DDR_D24,		
		SAC58R_PAD_DDR_D23__DDR_D23,		
		SAC58R_PAD_DDR_D22__DDR_D22,		
		SAC58R_PAD_DDR_D21__DDR_D21,		
		SAC58R_PAD_DDR_D20__DDR_D20,		
		SAC58R_PAD_DDR_D19__DDR_D19,		
		SAC58R_PAD_DDR_D18__DDR_D18,		
		SAC58R_PAD_DDR_D17__DDR_D17,		
		SAC58R_PAD_DDR_D16__DDR_D16,		
		SAC58R_PAD_DDR_D15__DDR_D15,		
		SAC58R_PAD_DDR_D14__DDR_D14,		
		SAC58R_PAD_DDR_D13__DDR_D13,		
		SAC58R_PAD_DDR_D12__DDR_D12,		
		SAC58R_PAD_DDR_D11__DDR_D11,		
		SAC58R_PAD_DDR_D10__DDR_D10,		
		SAC58R_PAD_DDR_D9__DDR_D9,		
		SAC58R_PAD_DDR_D8__DDR_D8,		
		SAC58R_PAD_DDR_D7__DDR_D7,		
		SAC58R_PAD_DDR_D6__DDR_D6,		
		SAC58R_PAD_DDR_D5__DDR_D5,		
		SAC58R_PAD_DDR_D4__DDR_D4,		
		SAC58R_PAD_DDR_D3__DDR_D3,		
		SAC58R_PAD_DDR_D2__DDR_D2,		
		SAC58R_PAD_DDR_D1__DDR_D1,		
		SAC58R_PAD_DDR_D0__DDR_D0,		
		SAC58R_PAD_DDR_DM1__DDR_DM3,		
		SAC58R_PAD_DDR_DM0__DDR_DM2,		
		SAC58R_PAD_DDR_DM1__DDR_DM1,		
		SAC58R_PAD_DDR_DM0__DDR_DM0,		
		SAC58R_PAD_DDR_DQS3__DDR_DQS3,	
		SAC58R_PAD_DDR_DQS0__DDR_DQS2,	
		SAC58R_PAD_DDR_DQS1__DDR_DQS1,	
		SAC58R_PAD_DDR_DQS0__DDR_DQS0,	
		SAC58R_PAD_DDR_RAS__DDR_RAS,		
		SAC58R_PAD_DDR_WE__DDR_WE_B,		
		SAC58R_PAD_DDR_ODT1__DDR_ODT0,	
		SAC58R_PAD_DDR_ODT0__DDR_ODT1,	
		SAC58R_PAD_DDR_ZQ__DDR_ZQ,
	};

	imx_iomux_v3_setup_multiple_pads(ddr_pads, ARRAY_SIZE(ddr_pads));
}

void ddr_phy_init(void)
{
#if 0
	struct ddrmr_regs *ddrmr = (struct ddrmr_regs *)DDR_BASE_ADDR;

	writel(DDRMC_PHY_DQ_TIMING, &ddrmr->phy[0]);
	writel(DDRMC_PHY_DQ_TIMING, &ddrmr->phy[16]);
	writel(DDRMC_PHY_DQ_TIMING, &ddrmr->phy[32]);
	writel(DDRMC_PHY_DQ_TIMING, &ddrmr->phy[48]);

	writel(DDRMC_PHY_DQS_TIMING, &ddrmr->phy[1]);
	writel(DDRMC_PHY_DQS_TIMING, &ddrmr->phy[17]);
	writel(DDRMC_PHY_DQS_TIMING, &ddrmr->phy[33]);
	writel(DDRMC_PHY_DQS_TIMING, &ddrmr->phy[49]);

	writel(DDRMC_PHY_CTRL, &ddrmr->phy[2]);
	writel(DDRMC_PHY_CTRL, &ddrmr->phy[18]);
	writel(DDRMC_PHY_CTRL, &ddrmr->phy[34]);
	writel(DDRMC_PHY_CTRL, &ddrmr->phy[50]);

	writel(DDRMC_PHY_MASTER_CTRL, &ddrmr->phy[3]);
	writel(DDRMC_PHY_MASTER_CTRL, &ddrmr->phy[19]);
	writel(DDRMC_PHY_MASTER_CTRL, &ddrmr->phy[35]);
	writel(DDRMC_PHY_MASTER_CTRL, &ddrmr->phy[51]);

	writel(DDRMC_PHY_SLAVE_CTRL, &ddrmr->phy[4]);
	writel(DDRMC_PHY_SLAVE_CTRL, &ddrmr->phy[20]);
	writel(DDRMC_PHY_SLAVE_CTRL, &ddrmr->phy[36]);
	writel(DDRMC_PHY_SLAVE_CTRL, &ddrmr->phy[52]);

	writel(DDRMC_PHY50_DDR3_MODE | DDRMC_PHY50_EN_SW_HALF_CYCLE,
		&ddrmr->phy[50]);
#endif
}

void ddr_ctrl_init(void)
{
	writel(0x00008000, 0x4016901C); //MDSCR
	writel(0x0000005F, 0x40169040); //MDASP (CS0_END=5F->  
	writel(0x00010600, 0x40169018); //MDMISC (DDR_TYPE=0->DDR3, DDR_4_BANK=0->8 banks, RALAT=0-> 0 read latency, MIF3_MODE=3-> prediction enable, WALAT=0-> 0 write lantency) 
	writel(0x03180000, 0x40169000); //MDCTL (DSIZ=16 bit data bus, BL=1->burst lenght 8, COL=3-> column add 8, ROW=3-> row add 14, SDE_0 and SDE_1= 0 CS enable)
	writel(0x40404040, 0x40169848); //MPRDDLCTL, 
	writel(0x40404040, 0x40169850); //MPWRDLCTL0
	writel(0x02000200, 0x4016980C); //MPWLDECTRL0
	writel(0x00000000, 0x4016983C); //MPDGCTRL0
	writel(0x00000000, 0x40169840); //MPDGCTRL1
	writel(0x40447544, 0x4016900C); //MDCFG0
	writel(0xB6948662, 0x40169010); //MDCFG1
	writel(0x01FF00DC, 0x40169014); //MDCFG2
	writel(0x000026D2, 0x4016902C); //MDRWD
	writel(0x00440101, 0x40169030); //MDOR
	writel(0x22335030, 0x40169008); //MDOTC (timing param)
	writel(0x00020024, 0x40169004); //MDPDC
	writel(0xC3180000, 0x40169000); //MDCTL (DSIZ=16 bit data bus, BL=1 burst lenght 8, COL=3 column add 8, ROW=3 row add 14, SDE_0 and SDE_1= 1 CS enable) 
	writel(0x00000800, 0x401698B8); //MPMUR
	writel(0x00008032, 0x4016901C); //MDSCR 1
	writel(0x0000803A, 0x4016901C); //MDSCR 2
	writel(0x00008033, 0x4016901C); //MDSCR 3
	writel(0x0000803B, 0x4016901C); //MDSCR 4
	writel(0x00468031, 0x4016901C); //MDSCR 5
	writel(0x00468039, 0x4016901C); //MDSCR 6
	writel(0x051080B0, 0x4016901C); //MDSCR 7
	writel(0x051080B8, 0x4016901C); //MDSCR 8
	writel(0x04008040, 0x4016901C); //MDSCR 9
	writel(0x04008048, 0x4016901C); //MDSCR 10
	writel(0xA5380003, 0x40169800); //MPZQHWCTRL
	writel(0x30B09800, 0x40169020); //MDREF
	writel(0x00033332, 0x40169818); //MPODTCTRL
	writel(0x00000000, 0x4016901C); //MDSCR
}

int dram_init(void)
{
#if 0
	setup_iomux_ddr();
	ddr_ctrl_init();
#endif
	gd->ram_size = get_ram_size((void *)PHYS_SDRAM, PHYS_SDRAM_SIZE);

	return 0;
}

static void setup_iomux_uart(void)
{
	static const iomux_v3_cfg_t uart_pads[] = {
		SAC58R_PAD_PH14__UART0_TX,
		SAC58R_PAD_PH15__UART0_RX,
		SAC58R_PAD_PF11__UART1_TX,
		SAC58R_PAD_PF12__UART1_RX,
		SAC58R_PAD_PL5__UART2_TX,
		SAC58R_PAD_PL4__UART2_RX,
		SAC58R_PAD_PE28__UART3_TX,
		SAC58R_PAD_PE27__UART3_RX,
		SAC58R_PAD_PH0__UART4_TX,
		SAC58R_PAD_PH1__UART4_RX,
		SAC58R_PAD_PH9__UART5_TX,
		SAC58R_PAD_PH10__UART5_RX,
	};

	imx_iomux_v3_setup_multiple_pads(uart_pads, ARRAY_SIZE(uart_pads));
}

static void setup_iomux_enet(void)
{
#if 0
	static const iomux_v3_cfg_t enet0_pads[] = {
		VF610_PAD_PTA6__RMII0_CLKIN,
		VF610_PAD_PTC1__RMII0_MDIO,
		VF610_PAD_PTC0__RMII0_MDC,
		VF610_PAD_PTC2__RMII0_CRS_DV,
		VF610_PAD_PTC3__RMII0_RD1,
		VF610_PAD_PTC4__RMII0_RD0,
		VF610_PAD_PTC5__RMII0_RXER,
		VF610_PAD_PTC6__RMII0_TD1,
		VF610_PAD_PTC7__RMII0_TD0,
		VF610_PAD_PTC8__RMII0_TXEN,
	};

	imx_iomux_v3_setup_multiple_pads(enet0_pads, ARRAY_SIZE(enet0_pads));
#endif
}

static void setup_iomux_i2c(void)
{

	static const iomux_v3_cfg_t i2c_pads[] = {
		SAC58R_PAD_PA0_I2C0_SDA,
		SAC58R_PAD_PA1_I2C0_SCL,
		SAC58R_PAD_PE19_I2C1_SCL,
		SAC58R_PAD_PE10_I2C1_SDA,
		SAC58R_PAD_PA8_I2C2_SDA,
		SAC58R_PAD_PA9_I2C2_SCL,
		SAC58R_PAD_PH2_I2C3_SCL,
		SAC58R_PAD_PH4_I2C3_SDA,
	};

	imx_iomux_v3_setup_multiple_pads(i2c_pads, ARRAY_SIZE(i2c_pads));
}

#ifdef CONFIG_SYS_USE_NAND
void setup_iomux_nfc(void)
{
#if 0
	static const iomux_v3_cfg_t nfc_pads[] = {
		VF610_PAD_PTD31__NFC_IO15,
		VF610_PAD_PTD30__NFC_IO14,
		VF610_PAD_PTD29__NFC_IO13,
		VF610_PAD_PTD28__NFC_IO12,
		VF610_PAD_PTD27__NFC_IO11,
		VF610_PAD_PTD26__NFC_IO10,
		VF610_PAD_PTD25__NFC_IO9,
		VF610_PAD_PTD24__NFC_IO8,
		VF610_PAD_PTD23__NFC_IO7,
		VF610_PAD_PTD22__NFC_IO6,
		VF610_PAD_PTD21__NFC_IO5,
		VF610_PAD_PTD20__NFC_IO4,
		VF610_PAD_PTD19__NFC_IO3,
		VF610_PAD_PTD18__NFC_IO2,
		VF610_PAD_PTD17__NFC_IO1,
		VF610_PAD_PTD16__NFC_IO0,
		VF610_PAD_PTB24__NFC_WEB,
		VF610_PAD_PTB25__NFC_CE0B,
		VF610_PAD_PTB27__NFC_REB,
		VF610_PAD_PTC26__NFC_RBB,
		VF610_PAD_PTC27__NFC_ALE,
		VF610_PAD_PTC28__NFC_CLE,
	};
	imx_iomux_v3_setup_multiple_pads(nfc_pads, ARRAY_SIZE(nfc_pads));
#endif
}
#endif

#ifdef CONFIG_FSL_ESDHC
struct fsl_esdhc_cfg esdhc_cfg[CONFIG_SYS_FSL_ESDHC_NUM] = {
	{USDHC0_BASE_ADDR},
	{USDHC1_BASE_ADDR},
	{USDHC2_BASE_ADDR},
};

int board_mmc_getcd(struct mmc *mmc)
{
	/* eSDHC0 is always present */
	return 1;
}

int board_mmc_init(bd_t *bis)
{
	int i;
	int ret;

	static const iomux_v3_cfg_t sdhc_pads[] = {
		SAC58R_PAD_PF0__SDHC0_CLK,
		SAC58R_PAD_PF1__SDHC0_CMD,
		SAC58R_PAD_PF2__SDHC0_DAT0,
		SAC58R_PAD_PF3__SDHC0_DAT1,
		SAC58R_PAD_PF4__SDHC0_DAT2,
		SAC58R_PAD_PF5__SDHC0_DAT3,
		SAC58R_PAD_PF0__SDHC0_CLK,
		SAC58R_PAD_PF1__SDHC0_CMD,
		SAC58R_PAD_PF2__SDHC0_DAT0,
		SAC58R_PAD_PF3__SDHC0_DAT1,
		SAC58R_PAD_PF4__SDHC0_DAT2,
		SAC58R_PAD_PF5__SDHC0_DAT3,
		SAC58R_PAD_PF26__SDHC1_CLK,
		SAC58R_PAD_PF27__SDHC1_CMD,
		SAC58R_PAD_PF22__SDHC1_DAT0,
		SAC58R_PAD_PF23__SDHC1_DAT1,
		SAC58R_PAD_PF19__SDHC1_DAT2,
		SAC58R_PAD_PF20__SDHC1_DAT3,
		SAC58R_PAD_PC12__SDHC2_CLK,
		SAC58R_PAD_PC13__SDHC2_CMD,
		SAC58R_PAD_PC9__SDHC2_DAT0,
		SAC58R_PAD_PC6__SDHC2_DAT1,
		SAC58R_PAD_PC5__SDHC2_DAT2,
		SAC58R_PAD_PC2__SDHC2_DAT3,
		SAC58R_PAD_PC10__SDHC2_DAT4,
		SAC58R_PAD_PC11__SDHC2_DAT5,
		SAC58R_PAD_PC7__SDHC2_DAT6,
		SAC58R_PAD_PC8__SDHC2_DAT7,
	};

	imx_iomux_v3_setup_multiple_pads(
		sdhc_pads, ARRAY_SIZE(sdhc_pads));

	/* Enable SDHCs modules in GPC */
	enable_periph_clk(AIPS2,AIPS2_OFF_SDHC0);
	enable_periph_clk(AIPS2,AIPS2_OFF_SDHC1);
	enable_periph_clk(AIPS2,AIPS2_OFF_SDHC2);

	for (i = 0; i < CONFIG_SYS_FSL_ESDHC_NUM; i++) {
		esdhc_cfg[i].sdhc_clk = mxc_get_clock(MXC_USDHC0_CLK + i);
		ret = fsl_esdhc_initialize(bis, &esdhc_cfg[i]);
		if (ret < 0) {
			printf("Warning: failed to initialize mmc dev %d\n", i);
		}
	}

	return 0;
}
#endif

static void clock_init(void)
{
	struct ccm_reg *ccm = (struct ccm_reg *)CCM_BASE_ADDR;
	struct anadig_reg *anadig = (struct anadig_reg *)ANADIG_BASE_ADDR;
	struct scsc_reg *scsc = (struct scsc_reg *)SCSC_BASE_ADDR;

	/* Enable some modules in GPC */
	enable_periph_clk(AIPS0, AIPS0_OFF_GPC);
	enable_periph_clk(AIPS0, AIPS0_OFF_SRC);
	enable_periph_clk(AIPS0, AIPS0_OFF_CCM);
	enable_periph_clk(AIPS0, AIPS0_OFF_SCSC);
	enable_periph_clk(AIPS0, AIPS0_OFF_CMU);
	enable_periph_clk(AIPS0, AIPS0_OFF_ANADIG);
	enable_periph_clk(AIPS0, AIPS0_OFF_IOMUXC);
	enable_periph_clk(AIPS0, AIPS0_OFF_WKUP);
	enable_periph_clk(AIPS0, AIPS0_OFF_PIT);
	enable_periph_clk(AIPS2, AIPS2_OFF_SDHC0);
	enable_periph_clk(AIPS1, AIPS1_OFF_UART0);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTA);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTB);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTC);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTD);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTE);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTF);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTG);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTH);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTJ);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTK);
	enable_periph_clk(AIPS0, AIPS0_OFF_PORTL);
	enable_periph_clk(AIPS0, AIPS0_OFF_GPIOC);
	enable_periph_clk(AIPS2, AIPS2_OFF_ENET);
	enable_periph_clk(AIPS2, AIPS2_OFF_MMDC);


#if 0
        /* enable FXOSC and SXOSC clocks */
        setbits_le32(&scsc->osc_ctrl, SCSC_OSC_FXOSC_EN | SCSC_OSC_SXOSC_EN);
        /* wait for FXOSC to be enabled */
        while(!(readl(&scsc->osc_ctrl) & SCSC_CTRL_FXOSC_RDY_MASK));
#endif

	/* enable PLL1 = PLL_CORE/ARM */
	clrsetbits_le32(&anadig->pll1_ctrl,
					ANADIG_PLL_CTRL_POWERDOWN | ANADIG_PLL_CTRL_BYPASS,
					ANADIG_PLL_CTRL_ENABLE);
	/* wait for PLL1 to be locked */
	while(!(readl(&anadig->pll1_ctrl) & ANADIG_PLL_CTRL_LOCK));

#if 0
        /* enable PLL2 = PLL_SYS528 */
        clrsetbits_le32(&anadig->pll2_ctrl, ANADIG_PLL_CTRL_POWERDOWN | ANADIG_PLL_CTRL_BYPASS, ANADIG_PLL_CTRL_ENABLE | ANADIG_PLL2_CTRL_DIV_SELECT);
        /* configure PLL2_PFD3 @ 413MHz = 528*(18/23) */
        clrsetbits_le32(&anadig->pll2_pfd, ANADIG_PLL_PFD3_CLKGATE_MASK, (0x17 << ANADIG_PLL_PFD3_FRAC_MASK));
        /* wait for PLL to be locked */
        while(!(readl(&anadig->pll2_ctrl) & ANADIG_PLL_CTRL_LOCK));
#endif

	/* configure ARM A7 clock => From PLL1 (PLL_CORE) = 1200/2 = 600MHz */
	writel( (0x1 << CCM_PREDIV_CTRL_OFFSET) | (0x3 << CCM_MUX_CTL_OFFSET), &ccm->a7_clk);

	/* SDHC0,1,2 clocks => from PLL_SYS/5 = 480/5 = 96 MHz */
	writel(CCM_MODULE_ENABLE_CTL_EN | (0x4<< CCM_PREDIV_CTRL_OFFSET)
		| (0x3 << CCM_MUX_CTL_OFFSET), &ccm->uSDHC0_perclk);
	writel(CCM_MODULE_ENABLE_CTL_EN | (0x4<< CCM_PREDIV_CTRL_OFFSET)
		| (0x3 << CCM_MUX_CTL_OFFSET), &ccm->uSDHC1_perclk);
	writel(CCM_MODULE_ENABLE_CTL_EN | (0x4<< CCM_PREDIV_CTRL_OFFSET)
		| (0x3 << CCM_MUX_CTL_OFFSET), &ccm->uSDHC2_perclk);

#if 0	
	clrsetbits_le32(&ccm->ccr, CCM_CCR_OSCNT_MASK,
		CCM_CCR_FIRC_EN | CCM_CCR_OSCNT(5));
	clrsetbits_le32(&ccm->ccsr, CCM_REG_CTRL_MASK,
		CCM_CCSR_PLL1_PFD_CLK_SEL(3) | CCM_CCSR_PLL2_PFD4_EN |
		CCM_CCSR_PLL2_PFD3_EN | CCM_CCSR_PLL2_PFD2_EN |
		CCM_CCSR_PLL2_PFD1_EN | CCM_CCSR_PLL1_PFD4_EN |
		CCM_CCSR_PLL1_PFD3_EN | CCM_CCSR_PLL1_PFD2_EN |
		CCM_CCSR_PLL1_PFD1_EN | CCM_CCSR_DDRC_CLK_SEL(1) |
		CCM_CCSR_FAST_CLK_SEL(1) | CCM_CCSR_SYS_CLK_SEL(4));
	clrsetbits_le32(&ccm->cacrr, CCM_REG_CTRL_MASK,
		CCM_CACRR_IPG_CLK_DIV(1) | CCM_CACRR_BUS_CLK_DIV(2) |
		CCM_CACRR_ARM_CLK_DIV(0));
	clrsetbits_le32(&ccm->cscmr1, CCM_REG_CTRL_MASK,
		CCM_CSCMR1_ESDHC1_CLK_SEL(3));
	clrsetbits_le32(&ccm->cscdr1, CCM_REG_CTRL_MASK,
		CCM_CSCDR1_RMII_CLK_EN);
	clrsetbits_le32(&ccm->cscdr2, CCM_REG_CTRL_MASK,
		CCM_CSCDR2_ESDHC1_EN | CCM_CSCDR2_ESDHC1_CLK_DIV(0) |
		CCM_CSCDR2_NFC_CLK_INV | CCM_CSCDR2_NFC_EN | CCM_CSCDR2_NFC_CLK_FRAC_DIV(4));
	clrsetbits_le32(&ccm->cscdr3,CCM_CSCDR3_NFC_PRE_DIV_MASK,
		CCM_CSCDR3_NFC_PRE_DIV(1));
	clrsetbits_le32(&ccm->cscmr2, CCM_REG_CTRL_MASK,
		CCM_CSCMR2_RMII_CLK_SEL(0));
#endif
}

static void mscm_init(void)
{
	struct mscm_ir *mscmir = (struct mscm_ir *)MSCM_IR_BASE_ADDR;
	int i;

	/* Interrupt Routing Configuration */
	for (i = 0; i < MSCM_IRSPRC_NUM; i++)
		writew(int_routing_conf[i], &mscmir->irsprc[i]);
}

static void dmamux_init(void)
{
	/* Example DMA CHANNEL MUXING FOR SAC58R. This function is not called */
	static const dmamux_cfg_t dma_channels [] = {
		DMAMUX_CHANNEL(DMAMUX_0, 0, SAC58R_DMAREQSRC_UART0_RX, 0, 1), /* DMAMUX 0, Channel 0 => UART0_RX, no trigger, channel enable */
		DMAMUX_CHANNEL(DMAMUX_1, 8, SAC58R_DMAREQSRC_PORTA, 0, 1), /* DMAMUX 1, Channel 8 => PORT_A, no trigger, channel enable */
		DMAMUX_CHANNEL(DMAMUX_2, 4, SAC58R_DMAREQSRC_SAI6_TX, 0, 1), /* DMAMUX 2, Channel 4  => SAI6_TX, no trigger, channel enable */
		DMAMUX_CHANNEL(DMAMUX_3, 12, SAC58R_DMAREQSRC_QSPIO_RX, 0, 1), /* DMAMUX 3, Channel 12 => QSPI0_TX, no trigger, channel enable */
	};
	imx_dmamux_setup_multiple_channels(dma_channels, ARRAY_SIZE(dma_channels));
}

int board_phy_config(struct phy_device *phydev)
{
	if (phydev->drv->config)
		phydev->drv->config(phydev);

	return 0;
}

int board_early_init_f(void)
{
	clock_init();
	mscm_init();

	setup_iomux_uart();
	setup_iomux_enet();
	setup_iomux_i2c();
#ifdef CONFIG_SYS_USE_NAND
	setup_iomux_nfc();
#endif
	return 0;
}

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

	return 0;
}

int checkboard(void)
{
	puts("Board: SAC58R Functional Validation Board\n");

	return 0;
}