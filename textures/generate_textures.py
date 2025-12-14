#!/usr/bin/env python3
"""
Generate high-quality, creative textures for cub3d project.
Creates detailed brick, stone, wood, and metal wall textures.
"""

from PIL import Image, ImageDraw, ImageFilter
import random
import math

def add_noise(img, intensity=10):
    """Add subtle noise to make texture more realistic."""
    pixels = img.load()
    width, height = img.size
    
    random.seed(42)
    for y in range(height):
        for x in range(width):
            r, g, b = pixels[x, y]
            noise = random.randint(-intensity, intensity)
            pixels[x, y] = (
                max(0, min(255, r + noise)),
                max(0, min(255, g + noise)),
                max(0, min(255, b + noise))
            )
    return img

def create_detailed_brick_wall(size, brick_color, mortar_color):
    """Create a detailed brick wall texture with realistic shading."""
    img = Image.new('RGB', (size, size), mortar_color)
    draw = ImageDraw.Draw(img)
    
    brick_width = size // 4
    brick_height = size // 8
    mortar_thickness = 2
    
    random.seed(123)
    
    for row in range(0, size + brick_height, brick_height):
        # Alternate brick pattern (running bond)
        offset = (brick_width // 2) if (row // brick_height) % 2 else 0
        
        for col in range(-brick_width, size + brick_width, brick_width):
            x = col + offset
            
            # Skip if outside bounds
            if x + brick_width < 0 or x > size:
                continue
            
            # Base brick color with variation
            color_var = random.randint(-15, 15)
            brick_r = max(0, min(255, brick_color[0] + color_var))
            brick_g = max(0, min(255, brick_color[1] + color_var))
            brick_b = max(0, min(255, brick_color[2] + color_var))
            
            # Draw brick rectangle
            x1 = x + mortar_thickness
            y1 = row + mortar_thickness
            x2 = x + brick_width - mortar_thickness
            y2 = row + brick_height - mortar_thickness
            
            draw.rectangle([x1, y1, x2, y2], fill=(brick_r, brick_g, brick_b))
            
            # Add highlight on top edge
            highlight = (
                min(255, brick_r + 30),
                min(255, brick_g + 30),
                min(255, brick_b + 30)
            )
            draw.line([x1, y1, x2, y1], fill=highlight, width=1)
            draw.line([x1, y1, x1, y1 + 2], fill=highlight, width=1)
            
            # Add shadow on bottom edge
            shadow = (
                max(0, brick_r - 30),
                max(0, brick_g - 30),
                max(0, brick_b - 30)
            )
            draw.line([x1, y2, x2, y2], fill=shadow, width=1)
            draw.line([x2, y1, x2, y2], fill=shadow, width=1)
            
            # Add some cracks/texture
            if random.random() < 0.3:
                crack_y = random.randint(y1 + 2, y2 - 2)
                crack_x1 = random.randint(x1 + 2, x1 + brick_width // 3)
                crack_x2 = crack_x1 + random.randint(3, 10)
                draw.line([crack_x1, crack_y, crack_x2, crack_y], fill=shadow, width=1)
    
    # Add subtle noise
    img = add_noise(img, 8)
    
    # Apply slight blur for smoothing
    img = img.filter(ImageFilter.GaussianBlur(radius=0.3))
    
    return img

def create_stone_wall(size, base_color):
    """Create a detailed stone wall texture with irregular blocks."""
    img = Image.new('RGB', (size, size), (60, 60, 65))  # Dark mortar
    draw = ImageDraw.Draw(img)
    
    random.seed(456)
    
    # Create irregular stone blocks
    blocks = []
    y = 2
    while y < size - 5:
        x = 2
        row_height = random.randint(size // 8, size // 6)
        
        while x < size - 5:
            block_width = random.randint(size // 6, size // 4)
            
            if x + block_width > size - 2:
                block_width = size - x - 2
            if y + row_height > size - 2:
                row_height = size - y - 2
            
            blocks.append((x, y, x + block_width, y + row_height))
            x += block_width + 2
        
        y += row_height + 2
    
    # Draw each stone block
    for x1, y1, x2, y2 in blocks:
        # Color variation for each block
        color_var = random.randint(-20, 20)
        stone_color = (
            max(0, min(255, base_color[0] + color_var)),
            max(0, min(255, base_color[1] + color_var)),
            max(0, min(255, base_color[2] + color_var))
        )
        
        draw.rectangle([x1, y1, x2, y2], fill=stone_color)
        
        # Add lighting effect
        highlight = (
            min(255, stone_color[0] + 25),
            min(255, stone_color[1] + 25),
            min(255, stone_color[2] + 25)
        )
        draw.line([x1, y1, x2, y1], fill=highlight, width=1)
        draw.line([x1, y1, x1, y2], fill=highlight, width=1)
        
        shadow = (
            max(0, stone_color[0] - 25),
            max(0, stone_color[1] - 25),
            max(0, stone_color[2] - 25)
        )
        draw.line([x1, y2, x2, y2], fill=shadow, width=1)
        draw.line([x2, y1, x2, y2], fill=shadow, width=1)
        
        # Add cracks and texture
        for _ in range(random.randint(1, 3)):
            if random.random() < 0.5:
                crack_x = random.randint(x1 + 2, x2 - 2)
                crack_y1 = random.randint(y1 + 2, y1 + (y2 - y1) // 2)
                crack_y2 = crack_y1 + random.randint(2, (y2 - y1) // 2)
                draw.line([crack_x, crack_y1, crack_x, crack_y2], fill=shadow, width=1)
    
    # Add noise
    img = add_noise(img, 12)
    
    # Slight blur
    img = img.filter(ImageFilter.GaussianBlur(radius=0.4))
    
    return img

def create_wooden_planks(size, wood_color):
    """Create wooden planks texture with grain."""
    img = Image.new('RGB', (size, size), wood_color)
    draw = ImageDraw.Draw(img)
    
    random.seed(789)
    
    # Draw horizontal planks
    plank_height = size // 6
    
    for y in range(0, size, plank_height):
        # Plank separator (darker line)
        separator_color = (
            max(0, wood_color[0] - 40),
            max(0, wood_color[1] - 40),
            max(0, wood_color[2] - 40)
        )
        draw.line([0, y, size, y], fill=separator_color, width=2)
        
        # Add wood grain (horizontal lines)
        for i in range(plank_height):
            grain_y = y + i
            if grain_y >= size:
                break
            
            # Vary the color slightly for grain effect
            grain_intensity = int(10 * math.sin(i * 0.5) + random.randint(-5, 5))
            grain_color = (
                max(0, min(255, wood_color[0] + grain_intensity)),
                max(0, min(255, wood_color[1] + grain_intensity)),
                max(0, min(255, wood_color[2] + grain_intensity))
            )
            
            # Draw grain with some randomness
            if random.random() < 0.3:
                x_start = random.randint(0, size // 4)
                x_end = random.randint(size - size // 4, size)
                draw.line([x_start, grain_y, x_end, grain_y], fill=grain_color, width=1)
        
        # Add knots in wood
        if random.random() < 0.4:
            knot_x = random.randint(5, size - 5)
            knot_y = y + random.randint(2, plank_height - 2)
            knot_size = random.randint(2, 4)
            knot_color = (
                max(0, wood_color[0] - 50),
                max(0, wood_color[1] - 50),
                max(0, wood_color[2] - 50)
            )
            draw.ellipse([knot_x - knot_size, knot_y - knot_size,
                         knot_x + knot_size, knot_y + knot_size],
                        fill=knot_color, outline=separator_color)
    
    # Add noise
    img = add_noise(img, 6)
    
    return img

def create_metal_wall(size, base_color):
    """Create a metallic wall texture with panels and rivets."""
    img = Image.new('RGB', (size, size), base_color)
    draw = ImageDraw.Draw(img)
    
    random.seed(321)
    
    panel_size = size // 2
    
    # Draw metal panels
    for row in range(2):
        for col in range(2):
            x = col * panel_size
            y = row * panel_size
            
            # Panel color variation
            color_var = random.randint(-10, 10)
            panel_color = (
                max(0, min(255, base_color[0] + color_var)),
                max(0, min(255, base_color[1] + color_var)),
                max(0, min(255, base_color[2] + color_var))
            )
            
            # Draw panel
            draw.rectangle([x + 2, y + 2, x + panel_size - 2, y + panel_size - 2],
                          fill=panel_color)
            
            # Add panel borders (darker)
            border_color = (
                max(0, panel_color[0] - 30),
                max(0, panel_color[1] - 30),
                max(0, panel_color[2] - 30)
            )
            draw.rectangle([x + 2, y + 2, x + panel_size - 2, y + panel_size - 2],
                          outline=border_color, width=1)
            
            # Add rivets at corners
            rivet_color = (
                max(0, base_color[0] - 50),
                max(0, base_color[1] - 50),
                max(0, base_color[2] - 50)
            )
            rivet_size = 2
            
            # Corner rivets
            corners = [
                (x + 4, y + 4),
                (x + panel_size - 4, y + 4),
                (x + 4, y + panel_size - 4),
                (x + panel_size - 4, y + panel_size - 4)
            ]
            
            for rx, ry in corners:
                draw.ellipse([rx - rivet_size, ry - rivet_size,
                            rx + rivet_size, ry + rivet_size],
                           fill=rivet_color, outline=border_color)
            
            # Add scratches
            for _ in range(random.randint(2, 4)):
                sx1 = x + random.randint(5, panel_size - 5)
                sy1 = y + random.randint(5, panel_size - 5)
                sx2 = sx1 + random.randint(-10, 10)
                sy2 = sy1 + random.randint(-10, 10)
                scratch_color = (
                    max(0, panel_color[0] - 20),
                    max(0, panel_color[1] - 20),
                    max(0, panel_color[2] - 20)
                )
                draw.line([sx1, sy1, sx2, sy2], fill=scratch_color, width=1)
    
    # Add subtle noise
    img = add_noise(img, 5)
    
    # Add metallic shine effect
    img = img.filter(ImageFilter.GaussianBlur(radius=0.2))
    
    return img

def main():
    size = 128  # Higher resolution for better quality
    
    print(f"🎨 Generating {size}x{size} high-quality textures...\n")
    
    # North wall - Red brick wall (detailed)
    print("Creating north.png - Detailed red brick wall...")
    north = create_detailed_brick_wall(size, (160, 45, 35), (90, 80, 75))
    north.save('north.png')
    print("✓ north.png created\n")
    
    # South wall - Stone wall (medieval style)
    print("Creating south.png - Stone wall...")
    south = create_stone_wall(size, (110, 105, 95))
    south.save('south.png')
    print("✓ south.png created\n")
    
    # East wall - Wooden planks
    print("Creating east.png - Wooden planks...")
    east = create_wooden_planks(size, (120, 85, 50))
    east.save('east.png')
    print("✓ east.png created\n")
    
    # West wall - Metal panels (sci-fi style)
    print("Creating west.png - Metal panels...")
    west = create_metal_wall(size, (100, 110, 120))
    west.save('west.png')
    print("✓ west.png created\n")
    
    print("=" * 50)
    print("✅ All high-quality textures created successfully!")
    print("=" * 50)
    print("\nTexture details:")
    print(f"  - Resolution: {size}x{size} pixels")
    print("  - North: Red brick wall with realistic shading")
    print("  - South: Medieval stone wall with irregular blocks")
    print("  - East: Wooden planks with grain and knots")
    print("  - West: Metallic panels with rivets and scratches")
    print("\nNext steps:")
    print("  1. Update your .cub map files:")
    print("     NO ./textures/north.png")
    print("     SO ./textures/south.png")
    print("     WE ./textures/west.png")
    print("     EA ./textures/east.png")
    print("\n  2. Implement texture loading in your code")
    print("  3. Test with: make && ./cub3d maps/test_fixed.cub")

if __name__ == "__main__":
    main()
