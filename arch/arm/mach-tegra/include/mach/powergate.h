/*
 * drivers/regulator/tegra-regulator.c
 *
 * Copyright (c) 2010 Google, Inc
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _MACH_TEGRA_POWERGATE_H_
#define _MACH_TEGRA_POWERGATE_H_

#if !defined(CONFIG_ICS)
#define TEGRA_POWERGATE_CPU	0
#define TEGRA_POWERGATE_3D	1
#else
#define TEGRA_POWERGATE_CPU     0
#define TEGRA_POWERGATE_CPU0    TEGRA_POWERGATE_CPU
#define TEGRA_POWERGATE_3D      1
#define TEGRA_POWERGATE_3D0     TEGRA_POWERGATE_3D
#endif
#define TEGRA_POWERGATE_VENC	2
#define TEGRA_POWERGATE_PCIE	3
#define TEGRA_POWERGATE_VDEC	4
#define TEGRA_POWERGATE_L2	5
#define TEGRA_POWERGATE_MPE	6
#define TEGRA_NUM_POWERGATE	7
#if defined(CONFIG_ICS)
#define TEGRA_CPU_POWERGATE_ID(cpu)     (TEGRA_POWERGATE_CPU)
#define TEGRA_IS_CPU_POWERGATE_ID(id)   ((id) == TEGRA_POWERGATE_CPU)

struct clk;
#endif


#if !defined(CONFIG_ICS)
int tegra_powergate_power_on(int id);
int tegra_powergate_power_off(int id);
#else
int tegra_powergate_mc_disable(int id);
int tegra_powergate_mc_enable(int id);
int tegra_powergate_mc_flush(int id);
int tegra_powergate_mc_flush_done(int id);
#endif
bool tegra_powergate_is_powered(int id);
int tegra_powergate_remove_clamping(int id);

#if !defined(CONFIG_ICS)
/* Must be called with clk disabled, and returns with clk enabled */
int tegra_powergate_sequence_power_up(int id, struct clk *clk);

#else
/*
 * Functions to powergate/un-powergate partitions.
 * Handle clk management in the API's.
 *
 * tegra_powergate_partition_with_clk_off() can be called with
 * clks ON. It disables all required clks.
 *
 * tegra_unpowergate_partition_with_clk_on() can be called with
 * all required clks OFF. Returns with all clks ON.
 *
 * Warning: In general drivers should take care of the module
 * clks and use tegra_powergate_partition() &
 * tegra_unpowergate_partition() API's.
 */
int tegra_powergate_partition_with_clk_off(int id);
int tegra_unpowergate_partition_with_clk_on(int id);

/*
 * Functions to powergate un-powergate partitions.
 * Drivers are responsible for clk enable-disable
 *
 * tegra_powergate_partition() should be called with all
 * required clks OFF. Drivers should disable clks BEFORE
 * calling this fucntion
 *
 * tegra_unpowergate_partition should be called with all
 * required clks OFF. Returns with all clks OFF. Drivers
 * should enable all clks AFTER this function
 */
int tegra_powergate_partition(int id);
int tegra_unpowergate_partition(int id);
#endif

#endif /* _MACH_TEGRA_POWERGATE_H_ */