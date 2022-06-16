Library IEEE;
USE IEEE.std_logic_1164.all;

entity requestHandler is
	port(	rst, clk: in std_logic; 
		systemInput : in std_logic_vector(1 downto 0); 
		data : in std_logic_vector(19 downto 0);
	     	systemOutput : out std_logic_vector(19 downto 0) 
	); 
end entity requestHandler;

architecture behavioral of requestHandler is

type state is (idle, waiting, update);

signal current_state, next_state: state;

begin

state_memory: process(clk,rst)
	begin
	  if rst = '1' then
	current_state <= idle;
	    elsif(clk = '1' and clk'event) then
	      current_state <= next_state;
	  end if;
	end process;

input : process(current_state, systemInput)

begin
	case current_state is
		when idle => if systemInput = "01" then
			     next_state <= waiting;
			     else next_state <= idle;
			     end if;
		when waiting => if systemInput = "10" then
			     next_state <= update;
			     else next_state <= waiting;
			     end if;
		when update => if systemInput = "11" then
			     next_state <= idle;
			     else next_state <= update;
			     end if;
	  end case;
end process;


output : process(current_state, systemInput)

begin
	case current_state is
		when idle => if systemInput = "01" then
			     systemOutput <= data;
			     end if;
		when waiting => if systemInput = "10" then
			        systemOutput <= data;
			     end if;
		when update => if systemInput = "11" then
			     systemOutput <= "00000000000000000000";
			     end if;
	end case;
end process;
end architecture;
			    

