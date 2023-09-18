using Gtk

# Utility

lerp(a::Float32, b::Float32, t::Float32)::Float32 = a + t * (b - a)

function lerp(a::NTuple{3,Float32}, b::NTuple{3,Float32}, t::Float32)::NTuple{3,Float32}
  return (a[1] + t * (b[1] - a[1]), a[2] + t * (b[2] - a[2]), a[3] + t * (b[3] - a[3]))
end

function normalize(values::Array{Float32, N})::Array{Float32, N} where N
  min, max = extrema(values)
  diff = max - min
  return [(x - min) / diff for x in values]
end

# Noise


p = UInt8[
  151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36,
  103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0,
  26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56,
  87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
  77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
  46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
  187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109,
  198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
  255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183,
  170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
  172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112,
  104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162,
  241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106,
  157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205,
  93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
]

perm = repeat(p, outer=2)

fade(t::Float32)::Float32 = t * t * t * (t * (t * 6.0f0 - 15.0f0) + 10.0f0)

function perlin(x::Float32)::Float32
  # Find unit square that contains point
  ix::Int32 = Int32(floor(x))

  # Find relative x, y of point in square
  fx::Float32 = x - Float32(ix)

  # Wrap the integer cells at 255
  ix = ix & 0xFF

  # Calculate hash values
  h0::UInt8 = perm[ix+1]
  h1::UInt8 = perm[ix+1+1]

  # Calculate the gradients
  gx0::Float32 = Float32((h0 & 0x0F) - 8)
  gx1::Float32 = Float32((h1 & 0x0F) - 8)

  # Calculate the dot products
  n0::Float32 = gx0 * fx
  n1::Float32 = gx1 * (fx - 1.0f0)

  # Compute fade curves
  u::Float32 = fade(fx)

  # Interpolate the two results
  return lerp(n0, n1, u)
end

function perlin(x::Float32, y::Float32)::Float32
  # Find unit square that contains point
  ix::Int32 = Int32(floor(x))
  iy::Int32 = Int32(floor(y))

  # Find relative x, y of point in square
  fx::Float32 = x - Float32(ix)
  fy::Float32 = y - Float32(iy)

  # Wrap the integer cells at 255
  ix = ix & 0xFF
  iy = iy & 0xFF

  # Calculate hash values

  h0::UInt8 = perm[ix+1]
  h1::UInt8 = perm[ix+1+1]

  h00::UInt8 = perm[h0+iy+1]
  h10::UInt8 = perm[h1+iy+1]
  h01::UInt8 = perm[h0+iy+1+1]
  h11::UInt8 = perm[h1+iy+1+1]

  # Calculate the gradients

  gx00::Float32 = Float32((h00 & 0x0F) - 8)
  gy00::Float32 = Float32(((h00 >> 4) & 0x0F) - 8)
  gx10::Float32 = Float32((h10 & 0x0F) - 8)
  gy10::Float32 = Float32(((h10 >> 4) & 0x0F) - 8)
  gx01::Float32 = Float32((h01 & 0x0F) - 8)
  gy01::Float32 = Float32(((h01 >> 4) & 0x0F) - 8)
  gx11::Float32 = Float32((h11 & 0x0F) - 8)
  gy11::Float32 = Float32(((h11 >> 4) & 0x0F) - 8)

  # Calculate the dot products

  n00::Float32 = gx00 * fx + gy00 * fy
  n10::Float32 = gx10 * (fx - 1.0f0) + gy10 * fy
  n01::Float32 = gx01 * fx + gy01 * (fy - 1.0f0)
  n11::Float32 = gx11 * (fx - 1.0f0) + gy11 * (fy - 1.0f0)

  # Compute fade curves

  u::Float32 = fade(fx)
  v::Float32 = fade(fy)

  # Interpolate the four results

  a::Float32 = lerp(n00, n10, u)
  b::Float32 = lerp(n01, n11, u)
  c::Float32 = lerp(a, b, v)

  return c
end

# Voronoi

function hash2(x::Float32, y::Float32)::NTuple{2,Float32}
  a::Float32 = sin(x * 127.1f0 + y * 311.7f0) * 43758.5453f0
  b::Float32 = sin(x * 269.5f0 + y * 183.3f0) * 43758.5453f0

  return (a - floor(a), b - floor(b))
end

function voronoi(x::Float32, y::Float32)
  
  # Implement voronoi noise 

  ix::Int32 = Int32(floor(x))
  iy::Int32 = Int32(floor(y))

  fx::Float32 = x - Float32(ix)
  fy::Float32 = y - Float32(iy)

  r::Float32 = 8.0f0

  for i in -1:1
    for j in -1:1
      h0, h1 = hash2(Float32(ix + i), Float32(iy + j))

      x = Float32(i) - fx + h0
      y = Float32(j) - fy + h1

      r = min(r, x * x + y * y)
    end
  end

  return sqrt(r)
end

# Fractal Brownian motion

function fbm(noise_function::Function, x::Float32, octaves::Int32, persistence::Float32)::Float32
  total::Float32 = 0.0f0
  amplitude::Float32 = 1.0f0

  for _ in 1:octaves
    total += noise_function(x) * amplitude
    x *= 2.0f0
    amplitude *= persistence
  end

  return total
end

function fbm(noise_function::Function, x::Float32, y::Float32, octaves::Int32, persistence::Float32)::Float32
  total::Float32 = 0.0f0
  amplitude::Float32 = 1.0f0

  for _ in 1:octaves
    total += noise_function(x, y) * amplitude
    x *= 2.0f0
    y *= 2.0f0
    amplitude *= persistence
  end

  return total
end

# Ocean waves

function ocean_waves(n::Int32, t::Float32, wave_speed::Float32)::Array{NTuple{3,Float32},1}
  # Generate ocean wave heights

  values = zeros(Float32, n)

  e = exp(1.0f0)
  x = 2 * pi * t * wave_speed
  cycle = floor(x / pi)
  x = mod(x, pi)

  wave = (sin(x) * e^(-x^2)) / 0.4f0 # 0 to 1
  dwave = -e^(-x^2)*(2*x*sin(x)-cos(x))

  noise = normalize([fbm(perlin, Float32(i) / n * 8, t * 2, Int32(6), 0.8f0) for i in 1:n])

  for i in 1:n
    x = Float32(i) / n

    if cycle % 2 == 1 # Change wave direction every cycle
      x = 1 - x
    end

    # Wave foam 

    foam = min(3 * x * wave, 1)

    # Dissolve foam using noise

    dissolve = dwave < 0

    if dissolve
      if noise[i] >= wave
        foam *= noise[i]
      end
    end

    values[i] = foam
  end

  # Generate colors

  shallow = (0.0f0, 0.3686274509803922f0, 0.7215686274509804f0) #005EB8
  deep = (0.0392156862745098f0, 0.6392156862745098f0, 0.8117647058823529f0) #0AA3CF

  colors = [lerp(shallow, deep, values[x]) for x in 1:n]

  return colors
end

# Lava

function lava(n::Int32, t::Float32, speed::Float32)::Array{NTuple{3,Float32},1}

  values = [fbm(voronoi, Float32(i) / n * 2, t * speed, Int32(6), 0.7f0) for i in 1:n]
  values = normalize(values)

  # Generate colors

  red = (0.81f0, 0.06f0, 0.13f0)
  orange = (0.85f0, 0.56f0, 0.06f0)

  colors = [lerp(red, orange, values[x]) for x in 1:n]

  return colors
end

# Breathing forest

function breathing_forest(n::Int32, t::Float32, speed::Float32, forest_scale::Float32)::Array{NTuple{3,Float32},1}
  # Wind 

  wind = perlin(t * speed) * 0.1f0
  wind_slope = wind - perlin((t - 0.1f0) * speed)
  wind_intensity = max(min(abs(wind_slope), 1.0f0), 0.1f0)

  # Forest

  forest = [fbm(perlin, (Float32(i) / n) * forest_scale + wind, Int32(6), 0.9f0) for i in 1:n]
  forest = normalize(forest)
  forest = [x * wind_intensity for x in forest]

  # Generate colors

  dark_green = (0.10f0, 0.66f0, 0.44f0)
  light_green = (0.72f0, 0.89f0, 0.78f0)

  colors = [lerp(dark_green, light_green, forest[x]) for x in 1:n]

  return colors
end

# Electricity

function electricity(n::Int32, t::Float32, speed::Float32)::Array{NTuple{3,Float32},1}
  values = [fbm(perlin, Float32(i) / n * 2, t * speed, Int32(6), 0.9f0) for i in 1:n]
  values = normalize(values)

  # Generate colors

  blue = (0.0f0, 0.0f0, 0.0f0)
  yellow = (1.0f0, 1.0f0, 0.0f0)

  colors = [lerp(blue, yellow, values[x]) for x in 1:n]

  return colors
end

# Galaxy Purple/Pink Nebula

function galaxy(n::Int32, t::Float32, speed::Float32)::Array{NTuple{3,Float32},1}
  values = [fbm(perlin, Float32(i) / n * 2, t * speed, Int32(6), 0.7f0) for i in 1:n]
  values = normalize(values)
  #values = [x * x for x in values]

  # Generate colors

  dark_blue = (0.0f0, 0.027450980392156862f0, 0.3803921568627451f0) #000761 
  dark_purple = (0.26666666666666666f0, 0.0f0, 0.5450980392156862f0) # 44008B
  dark_pink = (0.6235294117647059f0, 0.27058823529411763f0, 0.6901960784313725f0) # 9F45B0
  light_pink = (0.8980392156862745f0, 0.3058823529411765f0, 0.8156862745098039f0)  # E54ED0

  colors = [dark_blue for _ in 1:n]

  for i in 1:n
    t = values[i]

    if t < 0.33f0
      t = t / 0.33f0
      colors[i] = lerp(dark_blue, dark_purple, t)
    elseif t < 0.66f0
      t = (t - 0.33f0) / 0.33f0
      colors[i] = lerp(dark_purple, dark_pink, t)
    else
      t = (t - 0.66f0) / 0.33f0
      colors[i] = lerp(dark_pink, light_pink, t)
    end
  end

  return colors
end

# Initialization

display_map = false

width = Int32(64)
height = if display_map width else Int32(3) end
square_size = Int32(32)

window = GtkWindow("Effect Prototype", width * square_size, height * square_size)
window_canvas = GtkCanvas()

push!(window, window_canvas)

# Draw

function draw_noise(widget)
  ctx = getgc(widget)

  t = Int32(round(Int, time() * 1000) & 0x7FFFFFFF) / 1000.0f0

  # Effect
  #colors = ocean_waves(width, t, 0.1f0)
  #colors = lava(width, t, 0.02f0)
  #colors = breathing_forest(width, t, 0.2f0, 2.0f0)
  #colors = electricity(width, t, 0.6f0)
  colors = galaxy(width, t, 0.01f0)

  # Draw noise

  for x in 1:width
    color = colors[x]
    set_source_rgb(ctx, color[1], color[2], color[3])
    rectangle(ctx, (x - 1) * square_size, 0, square_size, height * square_size)
    fill(ctx)
  end
end

function draw_noise_map(widget)
  ctx = getgc(widget)
  
  noise = (x, y) -> fbm(voronoi, x / width, y / height, Int32(1), 0.5f0)
  scale = 4.0f0

  # 2D6A4F
  color1 = (0.0f0, 0.0f0, 0.0f0)
  # B7E4C7
  color2 = (1.0f0, 1.0f0, 1.0f0)

  noise_map = [noise(Float32(i) * scale, Float32(j) * scale) for i in 1:width, j in 1:height]
  noise_map = normalize(noise_map)

  for i in 1:width
    for j in 1:height
      n = noise_map[i, j]
      color = lerp(color1, color2, n)
      set_source_rgb(ctx, color[1], color[2], color[3])
      rectangle(ctx, (i - 1) * square_size, (j - 1) * square_size, square_size, square_size)
      fill(ctx)
    end
  end

end

# Loop

showall(window)

while true
  if display_map
    draw(draw_noise_map, window_canvas)
  else
    draw(draw_noise, window_canvas)
  end
  sleep(0.1)
end