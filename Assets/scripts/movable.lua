local friction = 4.815162342
local eps = 0.01

function MovingRight(dt, speed, cur_speed)
	return cur_speed + speed * dt
end

function MovingLeft(dt, speed, cur_speed)
	return cur_speed - speed * dt
end

function Idling(dt, speed, cur_speed)
	if cur_speed > eps then
		return cur_speed - friction * dt
	elseif cur_speed < -eps then
		return cur_speed + friction * dt
	end
	
	return cur_speed
end