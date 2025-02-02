import uiscriptlocale

LOCALE_PATH = uiscriptlocale.WINDOWS_PATH
ROOT_PATH = "d:/ymir work/ui/game/fishing/"

# 278 : 배경이미지 너비, 14 : 여백
WINDOW_WIDTH = 280 + 14
# 226 : 배경이미지 높이, 37 : 위아래 여백(타이틀) + 30 (타이머 높이28 + 여백 1씩)
WINDOW_HEIGHT = 226 + 37

window = {
	"name" : "FishingGameWindow",
	"style" : ("movable", "float", "limit", ),
		
	#"x" : (SCREEN_WIDTH / 2) - (WINDOW_WIDTH / 2),
	#"y" : (SCREEN_HEIGHT / 2) - (WINDOW_HEIGHT / 2),
	"x" : 0,
	"y" : 0,
	
	"width" : WINDOW_WIDTH,
	"height" : WINDOW_HEIGHT,
	
	"children" :
	[
		{
			"name" : "board",
			"type" : "board_with_titlebar",
			"style" : ("ltr", ),
			
			"x" : 0,
			"y" : 0,
			
			"width" : WINDOW_WIDTH,
			"height" : WINDOW_HEIGHT,
			"title" : uiscriptlocale.FISHING_RENEWAL_TITLE,
		
		
			"children" :
			(
				## BackGround Water
				{
					"name" : "fishing_background_water",
					"type" : "image",
					"style" : ("ltr", ),
					"x" : 7,
					"y" : 29,
					"image" : ROOT_PATH + "fishing_background_water.sub",
					
					"children" :
					(
						## BackGround Navigation Area
						{
							"name" : "fishing_water_navArea",
							"type" : "box",
							"style" : ("not_pick", "ltr", ),
							"x" : 15,
							"y" : 15,
							"width" : 278 - 30,
							"height" : 226 - 30,
							"color" : 0xFF35302D,
						},
						
						## Goal Circle
						{
							"name" : "fishing_goal_circle",
							"type" : "expanded_image",
							"style" : ("not_pick", "ltr", ),
							"x" : 68,
							"y" : 42,
							"image" : ROOT_PATH + "fishing_goal_circle.sub",
						},
					),
				},				
				
				
				## Goal Success Count
				{
					"name" : "fishing_goal_count",
					"type" : "expanded_image",
					"style" : ("ltr", ),
					"x" : 7 + 278 - 73,
					"y" : 29 + 5,
					"image" : ROOT_PATH + "fishing_goal_count.sub",
					
					"children" :
					(
						{ 
							"name" : "fishing_goal_count_text",
							"type" : "text",
							"style" : ("ltr", ),
							"x" : 45,
							"y" : 8, 
							"text" : "",
							"text_horizontal_align" : "center" 	
						},
					),
				},
				
				# Debug Text
				{ 
					"name" : "debug_text_fish_pos",
					"type" : "text", 
					"x" : 7,
					"y" : 29 + 5 + 8, 
					"text" : "",
					"text_horizontal_align" : "center" 	
				},
				
				{ 
					"name" : "debug_text_circle_pos",
					"type" : "text", 
					"x" : 7,
					"y" : 29 + 5 + 8 + 10, 
					"text" : "",
					"text_horizontal_align" : "center" 	
				},
				
				{ 
					"name" : "debug_text_mouse_pos",
					"type" : "text", 
					"x" : 7,
					"y" : 29 + 5 + 8 + 20, 
					"text" : "",
					"text_horizontal_align" : "center" 	
				},
				
				## Timer Base
				{
					"name" : "fishing_timer_baseImg",
					"type" : "image",
					"x" : 7 + 28,
					"y" : 223,
					"image" : ROOT_PATH + "fishing_timer_base.sub",
				},
				
				## Timer Gauge type expand_image ?
				{
					"name" : "fishing_timer_gauge",
					"type" : "expanded_image",
					"x" : 7 + 28,
					"y" : 223,
					"image" : ROOT_PATH + "fishing_timer_gauge.sub",
				},
			),
		},
	],
}
