Library IEEE;
USE IEEE.std_logic_1164.all;

entity testBench is
end entity;


architecture behavioral of testBench is

	


	component requestHandler is
		port(	rst, clk: in std_logic; 
			systemInput : in std_logic_vector(1 downto 0); 
			data : in std_logic_vector(19 downto 0);
	     		systemOutput : out std_logic_vector(19 downto 0) ); 
	end component;

	signal rst_TB: std_logic:= '0'; 
	signal clk_TB : std_logic := '0';
	signal systemInput_TB : std_logic_vector(1 downto 0) := "00"; 
	signal data_TB : std_logic_vector(19 downto 0) := "10101010101010101010";
	signal systemOutput_TB: std_logic_vector(19 downto 0);

	begin
	handler1 : requestHandler port map(	rst => rst_TB,
						clk => clk_TB,
						systemInput => systemInput_TB,
						data => data_TB,
						systemOutput => systemOutput_TB );
						 
	clck:process(clk_TB)
		begin
   			clk_TB <= not clk_TB after 0.5 ns;
	end process;

	sysInput:process(systemInput_TB)
		begin
   			systemInput_TB(0) <= not systemInput_TB(0) after 0.5 ns;
			systemInput_TB(1) <= not systemInput_TB(1) after 1.0 ns;
	end process;




end behavioral;


